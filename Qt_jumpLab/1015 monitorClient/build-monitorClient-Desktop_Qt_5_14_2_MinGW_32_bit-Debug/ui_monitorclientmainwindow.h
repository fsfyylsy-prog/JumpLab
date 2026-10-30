/********************************************************************************
** Form generated from reading UI file 'monitorclientmainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONITORCLIENTMAINWINDOW_H
#define UI_MONITORCLIENTMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_monitorClientMainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QHBoxLayout *connLayout;
    QLabel *label;
    QLineEdit *iplineEdit;
    QLabel *label_2;
    QLineEdit *portlineEdit;
    QPushButton *connectBtn;
    QLabel *showlabel;
    QSpacerItem *connSpacer;
    QLabel *weightLabel;
    QHBoxLayout *statsLayout;
    QHBoxLayout *bodyLayout;
    QTableWidget *tableWidget;
    QChartView *chartView;
    QGroupBox *fatigueGroup;
    QHBoxLayout *fatigueLayout;
    QLabel *fatigueValueLabel;
    QProgressBar *fatigueBar;
    QLabel *fatigueTipLabel;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *monitorClientMainWindow)
    {
        if (monitorClientMainWindow->objectName().isEmpty())
            monitorClientMainWindow->setObjectName(QString::fromUtf8("monitorClientMainWindow"));
        monitorClientMainWindow->resize(1400, 920);
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(9);
        monitorClientMainWindow->setFont(font);
        centralwidget = new QWidget(monitorClientMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("background:#0F172A;"));
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setSpacing(12);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(16, 12, 16, 12);
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        titleLabel->setFont(font1);
        titleLabel->setStyleSheet(QString::fromUtf8("color:#22D3EE;"));
        titleLabel->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(titleLabel);

        connLayout = new QHBoxLayout();
        connLayout->setObjectName(QString::fromUtf8("connLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("color:#CBD5E1;"));

        connLayout->addWidget(label);

        iplineEdit = new QLineEdit(centralwidget);
        iplineEdit->setObjectName(QString::fromUtf8("iplineEdit"));
        iplineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{background:#16213C;color:#E2E8F0;border:1px solid #2A3A52;border-radius:6px;padding:5px 8px;}\n"
"QLineEdit:focus{border:1px solid #22D3EE;}"));
        iplineEdit->setMinimumSize(QSize(150, 0));

        connLayout->addWidget(iplineEdit);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("color:#CBD5E1;"));

        connLayout->addWidget(label_2);

        portlineEdit = new QLineEdit(centralwidget);
        portlineEdit->setObjectName(QString::fromUtf8("portlineEdit"));
        portlineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{background:#16213C;color:#E2E8F0;border:1px solid #2A3A52;border-radius:6px;padding:5px 8px;}\n"
"QLineEdit:focus{border:1px solid #22D3EE;}"));
        portlineEdit->setMaximumSize(QSize(100, 16777215));

        connLayout->addWidget(portlineEdit);

        connectBtn = new QPushButton(centralwidget);
        connectBtn->setObjectName(QString::fromUtf8("connectBtn"));
        connectBtn->setStyleSheet(QString::fromUtf8("QPushButton{background:#22D3EE;color:#0B1220;border:none;border-radius:6px;padding:6px 18px;font-weight:bold;}\n"
"QPushButton:hover{background:#67E8F9;}\n"
"QPushButton:pressed{background:#0E7490;}\n"
"QPushButton:disabled{background:#334155;color:#64748B;}"));
        connectBtn->setMinimumSize(QSize(120, 34));

        connLayout->addWidget(connectBtn);

        showlabel = new QLabel(centralwidget);
        showlabel->setObjectName(QString::fromUtf8("showlabel"));
        showlabel->setStyleSheet(QString::fromUtf8("color:#64748B;font-weight:bold;"));

        connLayout->addWidget(showlabel);

        connSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        connLayout->addItem(connSpacer);

        weightLabel = new QLabel(centralwidget);
        weightLabel->setObjectName(QString::fromUtf8("weightLabel"));
        weightLabel->setStyleSheet(QString::fromUtf8("color:#94A3B8;"));

        connLayout->addWidget(weightLabel);


        mainLayout->addLayout(connLayout);

        statsLayout = new QHBoxLayout();
        statsLayout->setObjectName(QString::fromUtf8("statsLayout"));

        mainLayout->addLayout(statsLayout);

        bodyLayout = new QHBoxLayout();
        bodyLayout->setSpacing(14);
        bodyLayout->setObjectName(QString::fromUtf8("bodyLayout"));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setStyleSheet(QString::fromUtf8("QTableWidget{background:#16213C;alternate-background-color:#1A2438;color:#E2E8F0;gridline-color:#243349;border:1px solid #2A3A52;border-radius:8px;}\n"
"QTableWidget::item:selected{background:#0E7490;color:#F8FAFC;}\n"
"QHeaderView::section{background:#1B2637;color:#94A3B8;border:none;border-bottom:1px solid #2A3A52;padding:7px 4px;font-weight:bold;}\n"
"QScrollBar:vertical{background:#16213C;width:10px;border:none;}\n"
"QScrollBar::handle:vertical{background:#334155;border-radius:5px;min-height:24px;}\n"
"QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height:0;}"));
        tableWidget->setMinimumSize(QSize(420, 0));
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setAlternatingRowColors(true);

        bodyLayout->addWidget(tableWidget);

        chartView = new QChartView(centralwidget);
        chartView->setObjectName(QString::fromUtf8("chartView"));
        chartView->setStyleSheet(QString::fromUtf8("background:transparent;border:1px solid #2A3A52;border-radius:8px;"));
        chartView->setMinimumSize(QSize(560, 360));

        bodyLayout->addWidget(chartView);


        mainLayout->addLayout(bodyLayout);

        fatigueGroup = new QGroupBox(centralwidget);
        fatigueGroup->setObjectName(QString::fromUtf8("fatigueGroup"));
        fatigueGroup->setStyleSheet(QString::fromUtf8("QGroupBox{color:#94A3B8;border:1px solid #2A3A52;border-radius:8px;margin-top:14px;padding-top:6px;}\n"
"QGroupBox::title{subcontrol-origin:margin;subcontrol-position:top left;left:12px;padding:0 6px;color:#22D3EE;}"));
        fatigueLayout = new QHBoxLayout(fatigueGroup);
        fatigueLayout->setObjectName(QString::fromUtf8("fatigueLayout"));
        fatigueValueLabel = new QLabel(fatigueGroup);
        fatigueValueLabel->setObjectName(QString::fromUtf8("fatigueValueLabel"));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setWeight(75);
        fatigueValueLabel->setFont(font2);
        fatigueValueLabel->setStyleSheet(QString::fromUtf8("color:#F8FAFC;"));
        fatigueValueLabel->setMinimumSize(QSize(120, 0));
        fatigueValueLabel->setAlignment(Qt::AlignCenter);

        fatigueLayout->addWidget(fatigueValueLabel);

        fatigueBar = new QProgressBar(fatigueGroup);
        fatigueBar->setObjectName(QString::fromUtf8("fatigueBar"));
        fatigueBar->setStyleSheet(QString::fromUtf8("QProgressBar{border:none;background:#243044;border-radius:6px;height:14px;}\n"
"QProgressBar::chunk{background:#22C55E;border-radius:6px;}"));
        fatigueBar->setMaximum(100);
        fatigueBar->setValue(0);
        fatigueBar->setTextVisible(false);

        fatigueLayout->addWidget(fatigueBar);

        fatigueTipLabel = new QLabel(fatigueGroup);
        fatigueTipLabel->setObjectName(QString::fromUtf8("fatigueTipLabel"));
        fatigueTipLabel->setStyleSheet(QString::fromUtf8("color:#94A3B8;"));
        fatigueTipLabel->setMinimumSize(QSize(220, 0));

        fatigueLayout->addWidget(fatigueTipLabel);


        mainLayout->addWidget(fatigueGroup);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setStyleSheet(QString::fromUtf8("QTextEdit{background:#16213C;color:#E2E8F0;border:1px solid #2A3A52;border-radius:6px;padding:6px;}\n"
"QScrollBar:vertical{background:#16213C;width:10px;border:none;}\n"
"QScrollBar::handle:vertical{background:#334155;border-radius:5px;min-height:24px;}\n"
"QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height:0;}"));
        textEdit->setMaximumSize(QSize(16777215, 130));
        textEdit->setReadOnly(true);

        mainLayout->addWidget(textEdit);

        monitorClientMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(monitorClientMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1400, 21));
        menubar->setStyleSheet(QString::fromUtf8("background:#16213C;color:#CBD5E1;"));
        monitorClientMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(monitorClientMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background:#16213C;color:#94A3B8;"));
        monitorClientMainWindow->setStatusBar(statusbar);

        retranslateUi(monitorClientMainWindow);

        QMetaObject::connectSlotsByName(monitorClientMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *monitorClientMainWindow)
    {
        monitorClientMainWindow->setWindowTitle(QCoreApplication::translate("monitorClientMainWindow", "JumpLab \350\265\267\350\267\263\350\203\275\345\212\233\347\233\221\346\265\213\347\263\273\347\273\237 - \345\256\242\346\210\267\347\253\257", nullptr));
        titleLabel->setText(QCoreApplication::translate("monitorClientMainWindow", "JumpLab \302\267 \350\265\267\350\267\263\350\203\275\345\212\233\346\227\240\347\272\277\347\233\221\346\265\213\347\263\273\347\273\237\357\274\210\345\256\242\346\210\267\347\253\257\357\274\211", nullptr));
        label->setText(QCoreApplication::translate("monitorClientMainWindow", "\346\234\215\345\212\241\345\231\250 IP", nullptr));
        iplineEdit->setText(QCoreApplication::translate("monitorClientMainWindow", "127.0.0.1", nullptr));
        label_2->setText(QCoreApplication::translate("monitorClientMainWindow", "\347\253\257\345\217\243\345\217\267", nullptr));
        portlineEdit->setText(QCoreApplication::translate("monitorClientMainWindow", "8080", nullptr));
        connectBtn->setText(QCoreApplication::translate("monitorClientMainWindow", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250", nullptr));
        showlabel->setText(QCoreApplication::translate("monitorClientMainWindow", "\346\234\252\350\277\236\346\216\245", nullptr));
        weightLabel->setText(QCoreApplication::translate("monitorClientMainWindow", "\345\217\227\350\257\225\350\200\205\344\275\223\351\207\215\357\274\232--", nullptr));
        fatigueGroup->setTitle(QCoreApplication::translate("monitorClientMainWindow", "\347\226\262\345\212\263\346\214\207\346\225\260\357\274\210\345\237\272\344\272\216\346\234\200\350\277\221 10 \346\254\241\350\265\267\350\267\263\347\232\204\345\263\260\345\200\274\345\212\237\347\216\207\350\266\213\345\212\277\357\274\211", nullptr));
        fatigueValueLabel->setText(QCoreApplication::translate("monitorClientMainWindow", "--", nullptr));
        fatigueTipLabel->setText(QCoreApplication::translate("monitorClientMainWindow", "\347\255\211\345\276\205\346\225\260\346\215\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class monitorClientMainWindow: public Ui_monitorClientMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONITORCLIENTMAINWINDOW_H
