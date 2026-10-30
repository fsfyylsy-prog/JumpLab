#include "monitorservermainwindow.h"
#include "ui_monitorservermainwindow.h"

monitorServerMainWindow::monitorServerMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::monitorServerMainWindow)
    , task(nullptr)
    , onlineCount(0)
{
    ui->setupUi(this);

    //实例化套接字
    tcpServer=new QTcpServer(this);


    //如果有连接到来，自动发出信号 newConnection
    connect(tcpServer,&QTcpServer::newConnection,this,&monitorServerMainWindow::dealNewConnectionSlot);

    //QStringList ipList

    for(QHostAddress addr:QNetworkInterface::allAddresses())
    {
        //判断当前地址是否是ipv4
        if(addr.protocol()==QAbstractSocket::IPv4Protocol)
        {
            //将地址追加到容器

            ui->comboBox->addItem(addr.toString());
        }
    }
}

monitorServerMainWindow::~monitorServerMainWindow()
{
    delete ui;
}

//有连接，自动调用槽函数
void monitorServerMainWindow::dealNewConnectionSlot()
{
    //获取通信套接字描述符
    qintptr sockfd=tcpServer->nextPendingConnection()->socketDescriptor();

    qDebug()<<"主线程套接字描述符:"<<sockfd;

    //读取界面上的采集参数
    double weight=ui->weightSpinBox->value();//受试者体重(kg)
    int minMs=qRound(ui->minSpinBox->value()*1000);//最短起跳间隔(ms)
    int maxMs=qRound(ui->maxSpinBox->value()*1000);//最长起跳间隔(ms)
    if(maxMs<minMs)//防止用户把上限设得比下限还小
    {
        maxMs=minMs;
    }

    //传递给任务--子线程
    task=new myTask(sockfd,weight,minMs,maxMs);

    //信号槽连接
    //客户端下线后，任务类发来信号
    connect(task,&myTask::toMainSignal,this,&monitorServerMainWindow::dealtaskSignalSlot);
    connect(task,&myTask::offlineSignal,this,&monitorServerMainWindow::dealOfflineSlot);

    //获取全局线程对象，将任务交给线程池。调用run
    QThreadPool::globalInstance()->start(task);

    onlineCount++;
    updateStatLabel();

    ui->textEdit->append(QString("客户端接入，开始推送起跳数据（体重 %1 kg，间隔 %2 ~ %3 s）")
                         .arg(weight,0,'f',1)
                         .arg(ui->minSpinBox->value(),0,'f',1)
                         .arg(ui->maxSpinBox->value(),0,'f',1));
}


void monitorServerMainWindow::on_startBtn_clicked()
{

    //监听
    //QHostAddress::Any 本机所有网卡地址
    unsigned short port=ui->portlineEdit->text().toUShort();
    if(port==0)
    {
        port=8080;
    }
    tcpServer->listen(QHostAddress::Any,port);//这里不阻塞

    //设置按钮非使能
    ui->startBtn->setEnabled(false);

    //界面显示
    ui->textEdit->append(QString("服务器已启动，监听端口 %1").arg(port));
}

//任务类发来的信号，调用槽函数
void monitorServerMainWindow::dealtaskSignalSlot(QString msg)
{
    //将数据显示到界面
    ui->textEdit->append(msg);
}

//客户端下线，自动调用
void monitorServerMainWindow::dealOfflineSlot()
{
    onlineCount--;
    if(onlineCount<0)
    {
        onlineCount=0;
    }
    updateStatLabel();
}

void monitorServerMainWindow::updateStatLabel()
{
    ui->statLabel->setText(QString("在线客户端：%1").arg(onlineCount));
}
