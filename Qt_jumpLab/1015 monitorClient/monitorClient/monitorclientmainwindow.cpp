#include "monitorclientmainwindow.h"
#include "ui_monitorclientmainwindow.h"

//表格最多显示的行数
static const int MAX_ROWS=100;

//统计卡片的基础样式：卡片由代码动态创建，无法在 Designer 中预设，破纪录高亮结束后也恢复为此样式
static const char* CARD_STYLE="QFrame#statCard{background:#1B2637;border:1px solid #2A3A52;border-radius:10px;}";

monitorClientMainWindow::monitorClientMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::monitorClientMainWindow)
    , jumpCount(0)
    , bestHeight(0.0)
    , bestSpeed(0.0)
    , bestForce(0.0)
    , bestForceBW(0.0)
    , bestPower(0.0)
    , bestPowerPerKg(0.0)
    , sumPower(0.0)
{
    ui->setupUi(this);

    //实例化套接字
    tcpSocket=new QTcpSocket(this);

    //信号槽连接
    connect(tcpSocket,&QTcpSocket::connected,this,&monitorClientMainWindow::dealConnectSlot);
    connect(tcpSocket,&QTcpSocket::disconnected,this,&monitorClientMainWindow::dealDisconnectedSlot);
    connect(tcpSocket,&QTcpSocket::readyRead,this,&monitorClientMainWindow::dealReadyReadSlot);

    //表格与图表 1:1 等宽：图表拥有与表格相同的横向空间，三条曲线与三个 Y 轴可一次完整呈现
    ui->bodyLayout->setStretch(0,1);
    ui->bodyLayout->setStretch(1,1);

    //窗口最小尺寸，防止窗口被缩到图表元素显示不全
    setMinimumSize(1180,780);

    initTableWidget();
    initStatCards();
    initChartView();
}

monitorClientMainWindow::~monitorClientMainWindow()
{
    delete ui;
}

//初始化表
void monitorClientMainWindow::initTableWidget()
{
    //列数与表头由数据字段决定，只能在代码中设置
    //表格的配色、隔行变色、整行选中、禁止编辑、行高等外观与交互属性已在 .ui 的控件属性中完成
    ui->tableWidget->setColumnCount(5);
    QStringList labels={"序号","时间戳","起跳速度(m/s)","最大峰值力(N)","最大峰值功率(W)"};
    ui->tableWidget->setHorizontalHeaderLabels(labels);

    //以下三项 Designer 未暴露对应属性，只能在代码中设置
    //最后一列宽度自适应
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    //隐藏行号列、行高更舒展
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(28);
}

void monitorClientMainWindow::updateTable(info_t info)
{
    //插入空白行
    ui->tableWidget->insertRow(0);

    //峰值力同时给出牛顿值与倍体重，峰值功率同时给出绝对值与单位体重功率
    QString forceText=QString("%1  ( %2 BW )").arg(info.peakForce,0,'f',1).arg(info.peakForceBW,0,'f',2);
    QString powerText=QString("%1  ( %2 W/kg )").arg(info.peakPower,0,'f',1).arg(info.peakPowerPerKg,0,'f',1);

    //插入数据
    ui->tableWidget->setItem(0,0,new QTableWidgetItem(QString::number(info.seq)));
    ui->tableWidget->setItem(0,1,new QTableWidgetItem(info.time));
    ui->tableWidget->setItem(0,2,new QTableWidgetItem(QString::number(info.speed,'f',2)));
    ui->tableWidget->setItem(0,3,new QTableWidgetItem(forceText));
    ui->tableWidget->setItem(0,4,new QTableWidgetItem(powerText));

    //文字居中
    for(int col=0;col<ui->tableWidget->columnCount();col++)
    {
        if(ui->tableWidget->item(0,col))
        {
            ui->tableWidget->item(0,col)->setTextAlignment(Qt::AlignCenter);
        }
    }

    //设置只显示100条记录
    int count=ui->tableWidget->rowCount();
    if(count>MAX_ROWS)
    {
        //删除最后一行
        ui->tableWidget->removeRow(count-1);
    }
}

//==========功能一：成绩统计与"个人最佳 PB"面板==========

//创建统计卡片
void monitorClientMainWindow::initStatCards()
{
    QStringList titles={"起跳次数","最佳腾空高度 (cm)","最高起跳速度 (m/s)",
                        "最大峰值力 (N)","最大峰值功率 (W)","平均峰值功率 (W)"};
    for(const QString &title:titles)
    {
        cardValueLabels.append(createStatCard(title));
    }
}

//创建一张统计卡片：上方标题，下方大号数值
QLabel *monitorClientMainWindow::createStatCard(const QString &title)
{
    //统计卡片由代码动态创建（数量与标题在运行时确定），Designer 无法预设，故在此设置外观
    QFrame *card=new QFrame(this);
    card->setObjectName("statCard");
    card->setMinimumHeight(78);
    card->setStyleSheet(CARD_STYLE);

    QVBoxLayout *layout=new QVBoxLayout(card);
    layout->setSpacing(2);
    layout->setContentsMargins(10,8,10,8);

    QLabel *titleLabel=new QLabel(title,card);
    titleLabel->setObjectName("cardTitle");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color:#94A3B8;");

    QLabel *valueLabel=new QLabel("--",card);
    valueLabel->setObjectName("cardValue");
    valueLabel->setAlignment(Qt::AlignCenter);
    valueLabel->setStyleSheet("color:#F8FAFC;font-size:20px;font-weight:bold;");

    layout->addWidget(titleLabel);
    layout->addWidget(valueLabel);

    ui->statsLayout->addWidget(card);
    cardFrames.append(card);

    return valueLabel;
}

//刷新统计值，破纪录时对应卡片高亮
void monitorClientMainWindow::updateStats(const info_t &info)
{
    jumpCount=history.size();
    sumPower+=info.peakPower;

    //是否刷新了个人最佳
    bool newHeight=info.height>bestHeight;
    bool newSpeed=info.speed>bestSpeed;
    bool newForce=info.peakForce>bestForce;
    bool newPower=info.peakPower>bestPower;

    if(newHeight)
    {
        bestHeight=info.height;
    }
    if(newSpeed)
    {
        bestSpeed=info.speed;
    }
    if(newForce)
    {
        bestForce=info.peakForce;
        bestForceBW=info.peakForceBW;
    }
    if(newPower)
    {
        bestPower=info.peakPower;
        bestPowerPerKg=info.peakPowerPerKg;
    }

    //刷新卡片数值
    cardValueLabels.at(0)->setText(QString::number(jumpCount));
    cardValueLabels.at(1)->setText(QString::number(bestHeight,'f',1));
    cardValueLabels.at(2)->setText(QString::number(bestSpeed,'f',2));
    cardValueLabels.at(3)->setText(QString::number(bestForce,'f',0));
    cardValueLabels.at(4)->setText(QString::number(bestPower,'f',0));
    cardValueLabels.at(5)->setText(QString::number(sumPower/jumpCount,'f',0));

    //第一跳是基准，不算破纪录
    if(jumpCount<=1)
    {
        return;
    }

    //破纪录：卡片高亮 + 日志提示
    if(newHeight)
    {
        highlightCard(1);
        ui->textEdit->append(QString("★ 新纪录：腾空高度 %1 cm（第 %2 跳）").arg(bestHeight,0,'f',1).arg(info.seq));
    }
    if(newSpeed)
    {
        highlightCard(2);
        ui->textEdit->append(QString("★ 新纪录：起跳速度 %1 m/s（第 %2 跳）").arg(bestSpeed,0,'f',2).arg(info.seq));
    }
    if(newForce)
    {
        highlightCard(3);
        ui->textEdit->append(QString("★ 新纪录：峰值力 %1 N / %2 BW（第 %3 跳）")
                             .arg(bestForce,0,'f',1).arg(bestForceBW,0,'f',2).arg(info.seq));
    }
    if(newPower)
    {
        highlightCard(4);
        ui->textEdit->append(QString("★ 新纪录：峰值功率 %1 W / %2 W/kg（第 %3 跳）")
                             .arg(bestPower,0,'f',1).arg(bestPowerPerKg,0,'f',1).arg(info.seq));
    }
}

//卡片破纪录高亮 1.5 秒后恢复
void monitorClientMainWindow::highlightCard(int index)
{
    if(index<0||index>=cardFrames.size())
    {
        return;
    }

    QFrame *card=cardFrames.at(index);
    card->setStyleSheet("QFrame#statCard{background:#3B2F12;border:2px solid #FFD166;border-radius:10px;}");

    //1.5 秒后恢复卡片基础样式
    QTimer::singleShot(1500,card,[card]()
    {
        card->setStyleSheet(CARD_STYLE);
    });
}

//==========功能二：疲劳指数趋势分析==========

//疲劳指数 =（历史最佳连续 5 跳平均功率 - 最近 5 跳平均功率）/ 历史最佳平均功率
//再用最近 10 跳的最小二乘回归斜率判断功率是持续下降还是回升
void monitorClientMainWindow::updateFatigue()
{
    const int WIN=5;   //滑动窗口：5 次起跳
    const int TREND=10;//趋势窗口：10 次起跳

    if(history.size()<WIN)
    {
        ui->fatigueValueLabel->setText("--");
        ui->fatigueBar->setValue(0);
        ui->fatigueTipLabel->setText(QString("等待数据（还需 %1 次起跳）").arg(WIN-history.size()));
        return;
    }

    //1）基准值：历史所有窗口中，连续 WIN 跳平均功率的最高值，代表未疲劳时的输出水平
    double bestAvg=0.0;
    for(int i=0;i+WIN<=history.size();i++)
    {
        double sum=0.0;
        for(int j=0;j<WIN;j++)
        {
            sum+=history.at(i+j).peakPower;
        }
        bestAvg=qMax(bestAvg,sum/WIN);
    }

    //2）当前值：最近 WIN 跳的平均功率
    double recentSum=0.0;
    for(int i=history.size()-WIN;i<history.size();i++)
    {
        recentSum+=history.at(i).peakPower;
    }
    double recentAvg=recentSum/WIN;

    //3）疲劳指数：相对最佳水平的功率衰减百分比
    double fatigue=(bestAvg-recentAvg)/bestAvg*100.0;
    fatigue=qBound(0.0,fatigue,100.0);

    //4）最小二乘线性回归，求最近 TREND 跳的功率变化斜率 (W/次)
    int n=qMin(TREND,history.size());
    int start=history.size()-n;
    double sx=0.0,sy=0.0,sxy=0.0,sxx=0.0;
    for(int i=0;i<n;i++)
    {
        double x=i;//第 i 次
        double y=history.at(start+i).peakPower;
        sx+=x;
        sy+=y;
        sxy+=x*y;
        sxx+=x*x;
    }
    double denom=n*sxx-sx*sx;
    double slope=0.0;
    if(qAbs(denom)>1e-6)
    {
        slope=(n*sxy-sx*sy)/denom;
    }

    //5）分级判定：良好 / 轻度疲劳 / 重度疲劳
    QString color;
    QString tip;
    if(fatigue<12.0)
    {
        color="#22C55E";
        tip="状态良好，可继续测试";
    }
    else if(fatigue<25.0)
    {
        color="#F59E0B";
        tip="轻度疲劳，注意动作质量";
    }
    else
    {
        color="#EF4444";
        tip="重度疲劳，建议停止训练";
    }

    //叠加趋势描述
    if(slope<-1.0)
    {
        tip+=QString("（功率持续下降 %1 W/次）").arg(qAbs(slope),0,'f',1);
    }
    else if(slope>1.0)
    {
        tip+=QString("（功率回升 %1 W/次）").arg(slope,0,'f',1);
    }
    else
    {
        tip+="（功率基本平稳）";
    }

    ui->fatigueValueLabel->setText(QString::number(fatigue,'f',1)+"%");
    ui->fatigueValueLabel->setStyleSheet(QString("color:%1;font-size:22px;font-weight:bold;").arg(color));
    ui->fatigueBar->setValue(qRound(fatigue));
    ui->fatigueBar->setStyleSheet(QString("QProgressBar{border:none;background:#243044;border-radius:6px;}"
                                         "QProgressBar::chunk{background:%1;border-radius:6px;}").arg(color));
    ui->fatigueTipLabel->setText(tip);
    ui->fatigueTipLabel->setStyleSheet(QString("color:%1;").arg(color));
}

//坐标轴外观：轴标题与刻度文字使用与对应曲线相同的颜色，便于在多轴图里区分归属
static void setupAxisStyle(QValueAxis *axis,const QString &title,const QString &format,const QColor &color)
{
    axis->setTitleText(title);
    axis->setLabelFormat(format);
    axis->setTickCount(5);
    axis->setLabelsColor(color);
    axis->setTitleBrush(color);
    axis->setGridLineColor(QColor("#243349"));
}

//折线外观：名称、颜色、线宽
static void setupSeriesStyle(QLineSeries *series,const QString &name,const QColor &color)
{
    series->setName(name);
    series->setColor(color);
    QPen pen=series->pen();
    pen.setWidth(2);
    series->setPen(pen);
}

//初始化图表：单图多轴，三条曲线共享 X 轴，各自绑定独立 Y 轴
void monitorClientMainWindow::initChartView()
{
    //1.创建对象
    chart=new QChart;
    seriSpeed=new QLineSeries;
    seriForce=new QLineSeries;
    seriPower=new QLineSeries;
    axisX=new QValueAxis;
    axisYSpeed=new QValueAxis;
    axisYForce=new QValueAxis;
    axisYPower=new QValueAxis;

    //2.图表标题与深色主题
    chart->setTitle("起跳能力实时趋势");
    chart->setTheme(QChart::ChartThemeDark);
    //内边距压到最小，把横向空间全部留给绘图区与坐标轴
    chart->setMargins(QMargins(2,2,2,2));
    //图表背景、标题与界面配色统一
    chart->setBackgroundBrush(QColor("#16213C"));
    chart->setBackgroundRoundness(8);
    chart->setTitleBrush(QColor("#E2E8F0"));

    //3.三条折线：名称、颜色、线宽
    setupSeriesStyle(seriSpeed,"起跳速度 (m/s)",QColor("#22D3EE"));
    setupSeriesStyle(seriForce,"最大峰值力 (N)",QColor("#F59E0B"));
    setupSeriesStyle(seriPower,"最大峰值功率 (W)",QColor("#F472B6"));

    chart->addSeries(seriSpeed);
    chart->addSeries(seriForce);
    chart->addSeries(seriPower);

    //4.共享 X 轴：第几次起跳
    axisX->setRange(1,CHART_WINDOW);
    setupAxisStyle(axisX,"起跳序号","%d",QColor("#94A3B8"));
    axisX->setTickCount(6);
    chart->addAxis(axisX,Qt::AlignBottom);

    //5.三条曲线各自的 Y 轴：量纲不同，分别独立缩放
    //速度轴放左侧，峰值力与峰值功率依次放右侧，轴标题尽量短以节省横向空间
    axisYSpeed->setRange(0,4);
    setupAxisStyle(axisYSpeed,"速度 m/s","%.2f",QColor("#22D3EE"));
    chart->addAxis(axisYSpeed,Qt::AlignLeft);

    axisYForce->setRange(0,3500);
    setupAxisStyle(axisYForce,"峰值力 N","%.0f",QColor("#F59E0B"));
    chart->addAxis(axisYForce,Qt::AlignRight);

    axisYPower->setRange(0,5000);
    setupAxisStyle(axisYPower,"峰值功率 W","%.0f",QColor("#F472B6"));
    chart->addAxis(axisYPower,Qt::AlignRight);

    //6.曲线绑定坐标轴
    seriSpeed->attachAxis(axisX);
    seriSpeed->attachAxis(axisYSpeed);

    seriForce->attachAxis(axisX);
    seriForce->attachAxis(axisYForce);

    seriPower->attachAxis(axisX);
    seriPower->attachAxis(axisYPower);

    //7.图例放底部，用于区分三条曲线
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->legend()->setLabelColor(QColor("#CBD5E1"));

    //8.显示到界面，开启抗锯齿
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
    //关闭滚动条：图表整体自适应视图尺寸，不出现需要左右拖动的情况
    ui->chartView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->chartView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

//把一次起跳的数据点追加到三条折线
void monitorClientMainWindow::appendToCharts(const info_t &info)
{
    seriSpeed->append(info.seq,info.speed);
    seriForce->append(info.seq,info.peakForce);
    seriPower->append(info.seq,info.peakPower);

    //限制折线点数，防止长时间采集后内存与绘制压力过大
    while(seriSpeed->count()>MAX_POINTS) seriSpeed->remove(seriSpeed->at(0));
    while(seriForce->count()>MAX_POINTS) seriForce->remove(seriForce->at(0));
    while(seriPower->count()>MAX_POINTS) seriPower->remove(seriPower->at(0));

    //X 轴三条曲线共用，用速度曲线的数据点即可确定范围
    adjustXAxis(seriSpeed);
    //每条曲线按自己的 Y 轴缩放，量纲差异再大也不会被压成一条直线
    adjustChart(seriSpeed,axisYSpeed);
    adjustChart(seriForce,axisYForce);
    adjustChart(seriPower,axisYPower);
}

//X 轴：只显示最近 CHART_WINDOW 次起跳
void monitorClientMainWindow::adjustXAxis(QLineSeries *series)
{
    if(!series||!axisX||series->count()==0)
    {
        return;
    }

    int count=series->count();
    //窗口起点：只保留最近 CHART_WINDOW 个点参与显示与缩放
    int start=qMax(0,count-CHART_WINDOW);

    double firstX=series->at(start).x();
    double lastX=series->at(count-1).x();
    if(lastX-firstX<1)//至少保留一个跨度，避免数据点过少时坐标轴退化
    {
        lastX=firstX+1;
    }
    axisX->setRange(firstX,lastX);
}

//Y 轴：按窗口内该曲线的数据自动缩放
void monitorClientMainWindow::adjustChart(QLineSeries *series,QValueAxis *axisY)
{
    if(!series||!axisY||series->count()<2)
    {
        return;
    }

    int count=series->count();
    int start=qMax(0,count-CHART_WINDOW);

    //找出窗口内数据的最小值与最大值
    double minY=series->at(start).y();
    double maxY=minY;
    for(int i=start;i<count;i++)
    {
        double y=series->at(i).y();
        minY=qMin(minY,y);
        maxY=qMax(maxY,y);
    }

    //边距为极差的 15%，但不小于 0.5（防止数据恒定时范围为 0）
    double margin=qMax((maxY-minY)*0.15,0.5);

    axisY->setRange(minY-margin,maxY+margin);
}

//连接按钮槽函数
void monitorClientMainWindow::on_connectBtn_clicked()
{
    //获取界面ip端口
    QString ip=ui->iplineEdit->text();
    int port=ui->portlineEdit->text().toInt();
    //连接服务器
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

//网络连接后，自动调用
void monitorClientMainWindow::dealConnectSlot()
{
    ui->showlabel->setText("已连接");
    ui->textEdit->append("已连接到服务端，等待起跳数据...");
}

//断开连接，自动调用
void monitorClientMainWindow::dealDisconnectedSlot()
{
    ui->showlabel->setText("未连接");
    ui->textEdit->append("与服务端断开连接");
}

//有数据到来 ，自动调用槽函数
void monitorClientMainWindow::dealReadyReadSlot()
{
    //从套接字读数据
    //canReadLine()是Qt中QIODevice的成员函数(QTcpSocket继承于它)，用于判断当前缓冲区里是否已经有一行完整的数据可以读取
    while(tcpSocket->canReadLine())//是否可读，返回真则有数据可读
    {
        //读一行并去掉空白符
        QByteArray msg=tcpSocket->readLine().trimmed();
        QString str(msg);

        //解析json串
        QJsonDocument doc;
        doc=QJsonDocument::fromJson(msg);
        QJsonObject obj=doc.object();

        //只处理起跳记录
        if(obj.value("type").toString()!="jump")
        {
            continue;
        }

        //提取value 并封装到info_t包中
        info_t info;
        info.seq=obj.value("seq").toInt();
        info.time=obj.value("times").toString();
        info.weight=obj.value("weight").toString().toDouble();
        info.speed=obj.value("speed").toString().toDouble();
        info.height=obj.value("height").toString().toDouble();
        info.peakForce=obj.value("peakForce").toString().toDouble();
        info.peakForceBW=obj.value("peakForceBW").toString().toDouble();
        info.peakPower=obj.value("peakPower").toString().toDouble();
        info.peakPowerPerKg=obj.value("peakPowerPerKg").toString().toDouble();

        qDebug()<<"speed:"<<info.speed<<" height:"<<info.height
               <<" peakForce"<<info.peakForce<<" peakPower"<<info.peakPower;

        //日志区显示一行人类可读的摘要
        ui->textEdit->append(QString("第 %1 跳 | %2 | 速度 %3 m/s | 腾空 %4 cm | 峰值力 %5 N(%6 BW) | 峰值功率 %7 W(%8 W/kg)")
                             .arg(info.seq)
                             .arg(info.time)
                             .arg(info.speed,0,'f',2)
                             .arg(info.height,0,'f',1)
                             .arg(info.peakForce,0,'f',1)
                             .arg(info.peakForceBW,0,'f',2)
                             .arg(info.peakPower,0,'f',1)
                             .arg(info.peakPowerPerKg,0,'f',1));

        //显示服务端下发的受试者体重
        ui->weightLabel->setText(QString("受试者体重：%1 kg").arg(info.weight,0,'f',1));

        //保存历史记录，供成绩统计与疲劳分析使用
        history.append(info);
        if(history.size()>MAX_HISTORY)
        {
            history.removeFirst();
        }

        //将包数据更新到表
        updateTable(info);

        //刷新成绩统计与 PB 面板
        updateStats(info);

        //刷新疲劳指数
        updateFatigue();

        //向三张图表追加数据点
        appendToCharts(info);
    }
}
