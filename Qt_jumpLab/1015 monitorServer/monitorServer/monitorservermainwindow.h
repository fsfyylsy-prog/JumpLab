#ifndef MONITORSERVERMAINWINDOW_H
#define MONITORSERVERMAINWINDOW_H

#include <QMainWindow>
#include "mytask.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>

#include <QNetworkInterface>
#include <QThreadPool>

QT_BEGIN_NAMESPACE
namespace Ui { class monitorServerMainWindow; }
QT_END_NAMESPACE

class monitorServerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    monitorServerMainWindow(QWidget *parent = nullptr);
    ~monitorServerMainWindow();

    void dealNewConnectionSlot();

private slots:
    void on_startBtn_clicked();
    void dealtaskSignalSlot(QString msg);
    void dealOfflineSlot();//客户端下线，更新在线数量

private:
    void updateStatLabel();//刷新在线客户端数量

    Ui::monitorServerMainWindow *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    myTask *task;

    int onlineCount;//当前在线客户端数量
};
#endif // MONITORSERVERMAINWINDOW_H
