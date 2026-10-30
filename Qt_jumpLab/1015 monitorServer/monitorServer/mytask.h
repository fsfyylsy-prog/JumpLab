#ifndef MYTASK_H
#define MYTASK_H

#include <QObject>
#include <QRunnable>
#include <QDebug>
#include <QTcpSocket>
#include <QEventLoop>
#include <QThread>

#include<QRandomGenerator>//生成随机数类
#include <QTimer>//定时器类

#include <QHostAddress>

#include <QJsonObject>//构建 保存键值对的
#include <QJsonDocument>//将组件好的键值对，转换为
#include <QByteArray>
#include <QDateTime>//时间日期类

//起跳能力采集任务：每个客户端连接对应一个任务对象，在线程池中运行
//按"一次起跳 = 一条记录"的粒度，向客户端推送该次跳跃的力学指标
class myTask : public QObject,public QRunnable
{
    Q_OBJECT
public:
    //sockfd:通信套接字描述符
    //weightKg:受试者体重(kg)，用于把峰值力换算成倍体重、峰值功率换算成 W/kg
    //intervalMinMs/intervalMaxMs:两次起跳之间的随机间隔(毫秒)
    explicit myTask(qintptr sockfd,double weightKg,int intervalMinMs,int intervalMaxMs,QObject *parent = nullptr);
    void run() override;

    void dealDisconnectedSlot();
    void dealTimeOutSlot();

signals:
    void toMainSignal(QString);
    //客户端断开连接时通知主线程刷新在线数量
    void offlineSignal();

private:
    qintptr sockfd;//套接字描述符
    QTcpSocket *tcpSocket;//套接字
    QEventLoop *evenLoop;//事件循环

    QRandomGenerator *mrand;//随机数生成器

    QTimer *timer;//定时器

    QString ip;
    unsigned short port;

    double weight;//受试者体重(kg)
    int intervalMin;//最短起跳间隔(ms)
    int intervalMax;//最长起跳间隔(ms)
    int jumpSeq;//起跳序号(第几次起跳)

    //产生服从正态分布 N(mean,sigma^2) 的随机数（Box-Muller 变换）
    //真实人体运动数据围绕均值波动，用正态分布比均匀分布更贴近实际
    double gaussian(double mean,double sigma);

    //把 [min,max] 之外的随机波动截断，避免出现不合常理的极端值
    double clamped(double value,double min,double max);
};

#endif // MYTASK_H
