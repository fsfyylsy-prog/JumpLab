#include "mytask.h"

#include <cmath>

//重力加速度，用于腾空高度换算和体重->力(N)的换算
static const double G = 9.80665;

myTask::myTask(qintptr sockfd,double weightKg,int intervalMinMs,int intervalMaxMs,QObject *parent)
    : QObject(parent),sockfd(sockfd),weight(weightKg),
      intervalMin(intervalMinMs),intervalMax(intervalMaxMs),jumpSeq(0)
{
    //任务结束，自动删除当前对象
    setAutoDelete(true);
}

//Box-Muller 变换：把两个 [0,1) 均匀分布随机数转换为标准正态分布随机数
double myTask::gaussian(double mean,double sigma)
{
    double u1=mrand->generateDouble();
    double u2=mrand->generateDouble();
    if(u1<1e-9)//log(0) 无意义，给一个极小值兜底
    {
        u1=1e-9;
    }
    const double twoPi=6.28318530717958647692;
    double z=std::sqrt(-2.0*std::log(u1))*std::cos(twoPi*u2);
    return mean+sigma*z;
}

double myTask::clamped(double value,double min,double max)
{
    if(value<min) return min;
    if(value>max) return max;
    return value;
}

void myTask::run()
{
    qDebug()<<"套接字描述符"<<sockfd;
    //实例化套接字对象
    tcpSocket=new QTcpSocket;
    //设置套接字
    tcpSocket->setSocketDescriptor(sockfd);

    //获取客户端ip和端口
    ip=tcpSocket->peerAddress().toString();
    if(ip.startsWith("::ffff:"))
    {
        ip=ip.mid(7);//去掉"::ffff:"前缀
    }

    port=tcpSocket->peerPort();

    //实例化事件循环对象
    evenLoop=new QEventLoop;

    //断开连接,发出信号disconnected
    //发送者tcpSocket 在run实例化 属于子线程
    //this 是主窗口的task对象，在主线程实例化，属于主线程
    //发送者与接收者不在同一线程，默认槽函数在接收者线程执行  Qt::DirectConnection槽函数在发送者所在的线程执行
    connect(tcpSocket,&QTcpSocket::disconnected,this,&myTask::dealDisconnectedSlot,Qt::DirectConnection);

    //做任务 发送随机数据 准备工作
    //1）获取随机数生成器
    mrand=QRandomGenerator::global();

    //2)设置定时器
    timer=new QTimer;
    //一次起跳对应一条记录，两次起跳之间间隔随机，因此用单次触发定时器
    timer->setSingleShot(true);

    //3)信号槽连接 定时器到点后发出信号timeout
    connect(timer,&QTimer::timeout,this,&myTask::dealTimeOutSlot,Qt::DirectConnection);

    //4)启动定时器 随机间隔后产生第一次起跳
    timer->start(intervalMin+mrand->bounded(intervalMax-intervalMin+1));


    //开启事件循环 阻塞
    evenLoop->exec();

    qDebug()<<"run end";

    timer->stop();//停止定时器
    //释放堆对象
    delete timer;
    delete tcpSocket;
    delete evenLoop;
}

//断开连接，自动调用槽函数
void myTask::dealDisconnectedSlot()
{
    //拼接字符串并显示
    QString msg=QString("客户端 ip:%1 port:%2 已下线，本次会话共推送 %3 次起跳数据")
            .arg(ip).arg(port).arg(jumpSeq);

    //将数据发送到主线程显示
    emit toMainSignal(msg);

    //通知主线程：该客户端已断开，在线数量减一
    emit offlineSignal();

    //qDebug()<<"dealDisconnectedSlot 所在线程："<<QThread::currentThread();
    //关闭套接字
    tcpSocket->close();

    //退出事件循环
    if(evenLoop->isRunning())//如果正在运行
    {
        evenLoop->quit();//退出事件循环
    }
}

//定时器槽函数 生成一次起跳的力学指标 发送给客户端
void myTask::dealTimeOutSlot()
{
    jumpSeq++;//第几次起跳

    //----------1.疲劳衰减模型----------
    //连续纵跳时人体输出能力随跳跃次数下降，并逐渐趋于稳定（指数收敛）
    //跳到第 30 次衰减约 8%，跳到第 60 次衰减约 13%，最大衰减 18%
    double decay=1.0-0.18*(1.0-std::exp(-double(jumpSeq)/50.0));

    //----------2.起跳离地速度 v (m/s)----------
    //离地速度约 3.35 m/s，对应腾空高度 50~60 cm
    double speed=gaussian(3.35,0.15)*decay;
    speed=clamped(speed,2.20,4.00);

    //----------3.腾空高度 h = v^2 / (2g) (cm)----------
    //3.35 m/s -> 约 57 cm
    double heightCm=speed*speed/(2.0*G)*100.0;

    //----------4.最大峰值力 F (N) 与 倍体重 (BW)----------
    //纵跳蹬伸期地面反作用力峰值通常为 2~4 倍体重，疲劳时略有下降
    double bw=gaussian(2.85,0.45)*(0.90+0.10*decay);
    bw=clamped(bw,1.50,5.50);
    double peakForce=bw*weight*G;

    //----------5.最大峰值功率 P (W) 与 单位体重功率 (W/kg)----------
    //峰值功率并不等于"峰值力 × 离地速度"（二者不同时出现）
    //峰值功率出现在蹬伸中段，取峰值力的 0.55~0.80 倍与离地速度的乘积
    //70 kg 运动员在该速度下约为 4000~5000 W，即 55~70 W/kg
    double powerFactor=clamped(gaussian(0.675,0.045),0.55,0.80);
    double peakPower=peakForce*speed*powerFactor;
    double powerPerKg=peakPower/weight;

    qDebug()<<"第"<<jumpSeq<<"跳  速度:"<<speed<<"m/s  腾空:"<<heightCm
           <<"cm  峰值力:"<<peakForce<<"N("<<bw<<"BW)  峰值功率:"<<peakPower<<"W";

    //发给客户端
    QJsonObject obj;//创建json对象
    obj.insert("type","jump");//消息类型：一条起跳记录
    obj.insert("seq",jumpSeq);
    obj.insert("weight",QString::number(weight,'f',1));
    obj.insert("speed",QString::number(speed,'f',2));
    obj.insert("height",QString::number(heightCm,'f',1));
    obj.insert("peakForce",QString::number(peakForce,'f',1));
    obj.insert("peakForceBW",QString::number(bw,'f',2));
    obj.insert("peakPower",QString::number(peakPower,'f',1));
    obj.insert("peakPowerPerKg",QString::number(powerPerKg,'f',1));
    obj.insert("times",QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

    //创建文件对象
    QJsonDocument doc;
    doc.setObject(obj);

    QByteArray msg=doc.toJson(QJsonDocument::Compact)+'\n';//QJsonDocument::Compact：数据是单行

    tcpSocket->write(msg);

    //本次起跳已推送，随机等待一段时间后产生下一次起跳
    timer->start(intervalMin+mrand->bounded(intervalMax-intervalMin+1));
}
