#ifndef MONITORCLIENTMAINWINDOW_H
#define MONITORCLIENTMAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>

#include<QtCharts/QChartView>
using namespace QtCharts;

#include <QChart>//图表
#include <QChartView>//图表视图类
#include <QValueAxis>//数值轴
#include <QLineSeries>//折线


#include <QJsonObject>//构建 保存键值对的
#include <QJsonDocument>//将组件好的键值对，转换为可发送的json对象
#include <QByteArray>
#include <QDateTime>//时间日期类
#include <QTableWidgetItem>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QTimer>
#include <QList>

//一次起跳的完整指标包：服务端每检测到一次起跳推送一条
typedef struct
{
    int seq;              //第几次起跳
    QString time;         //时间戳
    double weight;        //受试者体重(kg)
    double speed;         //起跳离地速度(m/s)
    double height;        //腾空高度(cm)
    double peakForce;     //最大峰值力(N)
    double peakForceBW;   //最大峰值力(倍体重 BW)
    double peakPower;     //最大峰值功率(W)
    double peakPowerPerKg;//最大峰值功率(W/kg)
}info_t;


QT_BEGIN_NAMESPACE
namespace Ui { class monitorClientMainWindow; }
QT_END_NAMESPACE

class monitorClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    monitorClientMainWindow(QWidget *parent = nullptr);
    ~monitorClientMainWindow();

    void initTableWidget();
    void updateTable(info_t info);

    //功能一：成绩统计与"个人最佳 PB"面板
    void initStatCards();                                  //创建统计卡片
    QLabel *createStatCard(const QString &title);          //创建一张卡片，返回数值标签
    void updateStats(const info_t &info);                  //刷新统计值，破纪录时高亮
    void highlightCard(int index);                         //卡片破纪录高亮 1.5 秒

    //功能二：疲劳指数趋势分析
    void updateFatigue();

    void initChartView();

    //把一次起跳的数据点追加到三条折线，并调整坐标轴显示范围
    void appendToCharts(const info_t &info);
    //X 轴：三条曲线共用，只显示最近 CHART_WINDOW 次起跳
    void adjustXAxis(QLineSeries *series);
    //Y 轴：每条曲线绑定各自的 Y 轴，按窗口内数据自动缩放
    void adjustChart(QLineSeries *series,QValueAxis *axisY);

private slots:
    void on_connectBtn_clicked();

    void dealConnectSlot();
    void dealDisconnectedSlot();
    void dealReadyReadSlot();


private:
    Ui::monitorClientMainWindow *ui;
    QTcpSocket *tcpSocket;//套接字

    QList<info_t> history;//历史起跳记录，用于成绩统计与疲劳分析

    //统计卡片的容器与数值标签
    QList<QFrame*> cardFrames;
    QList<QLabel*> cardValueLabels;

    //成绩统计：个人最佳 PB
    int jumpCount;         //起跳次数
    double bestHeight;     //最佳腾空高度(cm)
    double bestSpeed;      //最高起跳速度(m/s)
    double bestForce;      //最大峰值力(N)
    double bestForceBW;    //最大峰值力对应的倍体重
    double bestPower;      //最大峰值功率(W)
    double bestPowerPerKg; //最大峰值功率对应的单位体重功率
    double sumPower;       //峰值功率累计值，用于求平均

    //单图多轴：三条曲线共享 X 轴，各自绑定独立 Y 轴
    QChart *chart;

    QLineSeries *seriSpeed;//起跳速度曲线
    QLineSeries *seriForce;//最大峰值力曲线
    QLineSeries *seriPower;//最大峰值功率曲线

    QValueAxis *axisX;//X 轴：起跳序号

    QValueAxis *axisYSpeed;//左侧 Y 轴：速度
    QValueAxis *axisYForce;//右侧 Y 轴：峰值力
    QValueAxis *axisYPower;//最右侧 Y 轴：峰值功率

    //曲线显示最近多少次起跳
    static const int CHART_WINDOW=30;
    //折线最多保留的数据点数
    static const int MAX_POINTS=300;
    //历史记录最多保留条数（供成绩统计与疲劳分析使用）
    static const int MAX_HISTORY=300;
};
#endif // MONITORCLIENTMAINWINDOW_H
