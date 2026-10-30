/********************************************************************************
** Form generated from reading UI file 'monitorservermainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONITORSERVERMAINWINDOW_H
#define UI_MONITORSERVERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_monitorServerMainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QGroupBox *cfgGroup;
    QFormLayout *formLayout;
    QLabel *label_ip;
    QComboBox *comboBox;
    QLabel *label_port;
    QLineEdit *portlineEdit;
    QLabel *label_weight;
    QDoubleSpinBox *weightSpinBox;
    QLabel *label_interval;
    QHBoxLayout *rangeLayout;
    QDoubleSpinBox *minSpinBox;
    QLabel *label_wave;
    QDoubleSpinBox *maxSpinBox;
    QSpacerItem *rangeSpacer;
    QHBoxLayout *btnLayout;
    QPushButton *startBtn;
    QLabel *statLabel;
    QSpacerItem *btnSpacer;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *monitorServerMainWindow)
    {
        if (monitorServerMainWindow->objectName().isEmpty())
            monitorServerMainWindow->setObjectName(QString::fromUtf8("monitorServerMainWindow"));
        monitorServerMainWindow->resize(900, 680);
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(9);
        monitorServerMainWindow->setFont(font);
        centralwidget = new QWidget(monitorServerMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setStyleSheet(QString::fromUtf8("background:#0F172A;"));
        mainLayout = new QVBoxLayout(centralwidget);
        mainLayout->setSpacing(14);
        mainLayout->setObjectName(QString::fromUtf8("mainLayout"));
        mainLayout->setContentsMargins(18, 14, 18, 14);
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setWeight(75);
        titleLabel->setFont(font1);
        titleLabel->setStyleSheet(QString::fromUtf8("color:#22D3EE;"));
        titleLabel->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(titleLabel);

        cfgGroup = new QGroupBox(centralwidget);
        cfgGroup->setObjectName(QString::fromUtf8("cfgGroup"));
        cfgGroup->setStyleSheet(QString::fromUtf8("QGroupBox{color:#94A3B8;border:1px solid #2A3A52;border-radius:8px;margin-top:14px;padding-top:8px;}\n"
"QGroupBox::title{subcontrol-origin:margin;subcontrol-position:top left;left:12px;padding:0 6px;color:#22D3EE;}"));
        formLayout = new QFormLayout(cfgGroup);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignVCenter);
        label_ip = new QLabel(cfgGroup);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));
        label_ip->setStyleSheet(QString::fromUtf8("color:#CBD5E1;"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_ip);

        comboBox = new QComboBox(cfgGroup);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox{background:#16213C;color:#E2E8F0;border:1px solid #2A3A52;border-radius:6px;padding:5px 8px;}\n"
"QComboBox::drop-down{border:none;width:20px;}\n"
"QComboBox QAbstractItemView{background:#16213C;color:#E2E8F0;selection-background-color:#0E7490;border:1px solid #2A3A52;}"));

        formLayout->setWidget(0, QFormLayout::FieldRole, comboBox);

        label_port = new QLabel(cfgGroup);
        label_port->setObjectName(QString::fromUtf8("label_port"));
        label_port->setStyleSheet(QString::fromUtf8("color:#CBD5E1;"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_port);

        portlineEdit = new QLineEdit(cfgGroup);
        portlineEdit->setObjectName(QString::fromUtf8("portlineEdit"));
        portlineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{background:#16213C;color:#E2E8F0;border:1px solid #2A3A52;border-radius:6px;padding:5px 8px;}\n"
"QLineEdit:focus{border:1px solid #22D3EE;}"));

        formLayout->setWidget(1, QFormLayout::FieldRole, portlineEdit);

        label_weight = new QLabel(cfgGroup);
        label_weight->setObjectName(QString::fromUtf8("label_weight"));
        label_weight->setStyleSheet(QString::fromUtf8("color:#CBD5E1;"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_weight);

        weightSpinBox = new QDoubleSpinBox(cfgGroup);
        weightSpinBox->setObjectName(QString::fromUtf8("weightSpinBox"));
        weightSpinBox->setStyleSheet(QString::fromUtf8("QDoubleSpinBox{background:#16213C;color:#E2E8F0;border:1px solid #2A3A52;border-radius:6px;padding:5px 8px;}\n"
"QDoubleSpinBox:focus{border:1px solid #22D3EE;}"));
        weightSpinBox->setDecimals(1);
        weightSpinBox->setMinimum(30.000000000000000);
        weightSpinBox->setMaximum(150.000000000000000);
        weightSpinBox->setSingleStep(0.500000000000000);
        weightSpinBox->setValue(70.000000000000000);

        formLayout->setWidget(2, QFormLayout::FieldRole, weightSpinBox);

        label_interval = new QLabel(cfgGroup);
        label_interval->setObjectName(QString::fromUtf8("label_interval"));
        label_interval->setStyleSheet(QString::fromUtf8("color:#CBD5E1;"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_interval);

        rangeLayout = new QHBoxLayout();
        rangeLayout->setObjectName(QString::fromUtf8("rangeLayout"));
        minSpinBox = new QDoubleSpinBox(cfgGroup);
        minSpinBox->setObjectName(QString::fromUtf8("minSpinBox"));
        minSpinBox->setStyleSheet(QString::fromUtf8("QDoubleSpinBox{background:#16213C;color:#E2E8F0;border:1px solid #2A3A52;border-radius:6px;padding:5px 8px;}\n"
"QDoubleSpinBox:focus{border:1px solid #22D3EE;}"));
        minSpinBox->setDecimals(1);
        minSpinBox->setMinimum(1.000000000000000);
        minSpinBox->setMaximum(20.000000000000000);
        minSpinBox->setSingleStep(0.500000000000000);
        minSpinBox->setValue(2.500000000000000);

        rangeLayout->addWidget(minSpinBox);

        label_wave = new QLabel(cfgGroup);
        label_wave->setObjectName(QString::fromUtf8("label_wave"));
        label_wave->setStyleSheet(QString::fromUtf8("color:#94A3B8;"));
        label_wave->setAlignment(Qt::AlignCenter);

        rangeLayout->addWidget(label_wave);

        maxSpinBox = new QDoubleSpinBox(cfgGroup);
        maxSpinBox->setObjectName(QString::fromUtf8("maxSpinBox"));
        maxSpinBox->setStyleSheet(QString::fromUtf8("QDoubleSpinBox{background:#16213C;color:#E2E8F0;border:1px solid #2A3A52;border-radius:6px;padding:5px 8px;}\n"
"QDoubleSpinBox:focus{border:1px solid #22D3EE;}"));
        maxSpinBox->setDecimals(1);
        maxSpinBox->setMinimum(1.000000000000000);
        maxSpinBox->setMaximum(20.000000000000000);
        maxSpinBox->setSingleStep(0.500000000000000);
        maxSpinBox->setValue(4.500000000000000);

        rangeLayout->addWidget(maxSpinBox);

        rangeSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        rangeLayout->addItem(rangeSpacer);


        formLayout->setLayout(3, QFormLayout::FieldRole, rangeLayout);


        mainLayout->addWidget(cfgGroup);

        btnLayout = new QHBoxLayout();
        btnLayout->setObjectName(QString::fromUtf8("btnLayout"));
        startBtn = new QPushButton(centralwidget);
        startBtn->setObjectName(QString::fromUtf8("startBtn"));
        startBtn->setStyleSheet(QString::fromUtf8("QPushButton{background:#22D3EE;color:#0B1220;border:none;border-radius:6px;padding:6px 18px;font-weight:bold;}\n"
"QPushButton:hover{background:#67E8F9;}\n"
"QPushButton:pressed{background:#0E7490;}\n"
"QPushButton:disabled{background:#334155;color:#64748B;}"));
        startBtn->setMinimumSize(QSize(140, 36));

        btnLayout->addWidget(startBtn);

        statLabel = new QLabel(centralwidget);
        statLabel->setObjectName(QString::fromUtf8("statLabel"));
        statLabel->setStyleSheet(QString::fromUtf8("color:#22C55E;font-weight:bold;"));

        btnLayout->addWidget(statLabel);

        btnSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        btnLayout->addItem(btnSpacer);


        mainLayout->addLayout(btnLayout);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setStyleSheet(QString::fromUtf8("QTextEdit{background:#16213C;color:#E2E8F0;border:1px solid #2A3A52;border-radius:6px;padding:6px;}\n"
"QScrollBar:vertical{background:#16213C;width:10px;border:none;}\n"
"QScrollBar::handle:vertical{background:#334155;border-radius:5px;min-height:24px;}\n"
"QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height:0;}"));
        textEdit->setReadOnly(true);

        mainLayout->addWidget(textEdit);

        monitorServerMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(monitorServerMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 21));
        menubar->setStyleSheet(QString::fromUtf8("background:#16213C;color:#CBD5E1;"));
        monitorServerMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(monitorServerMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background:#16213C;color:#94A3B8;"));
        monitorServerMainWindow->setStatusBar(statusbar);

        retranslateUi(monitorServerMainWindow);

        QMetaObject::connectSlotsByName(monitorServerMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *monitorServerMainWindow)
    {
        monitorServerMainWindow->setWindowTitle(QCoreApplication::translate("monitorServerMainWindow", "JumpLab \350\265\267\350\267\263\350\203\275\345\212\233\347\233\221\346\265\213\347\263\273\347\273\237 - \346\234\215\345\212\241\347\253\257", nullptr));
        titleLabel->setText(QCoreApplication::translate("monitorServerMainWindow", "JumpLab \302\267 \350\265\267\350\267\263\350\203\275\345\212\233\346\227\240\347\272\277\347\233\221\346\265\213\347\263\273\347\273\237\357\274\210\346\234\215\345\212\241\347\253\257\357\274\211", nullptr));
        cfgGroup->setTitle(QCoreApplication::translate("monitorServerMainWindow", "\351\207\207\351\233\206\345\217\202\346\225\260\351\205\215\347\275\256", nullptr));
        label_ip->setText(QCoreApplication::translate("monitorServerMainWindow", "\347\233\221\345\220\254\345\234\260\345\235\200", nullptr));
        label_port->setText(QCoreApplication::translate("monitorServerMainWindow", "\347\233\221\345\220\254\347\253\257\345\217\243", nullptr));
        portlineEdit->setText(QCoreApplication::translate("monitorServerMainWindow", "8080", nullptr));
        label_weight->setText(QCoreApplication::translate("monitorServerMainWindow", "\345\217\227\350\257\225\350\200\205\344\275\223\351\207\215 (kg)", nullptr));
        label_interval->setText(QCoreApplication::translate("monitorServerMainWindow", "\350\265\267\350\267\263\351\227\264\351\232\224 (\347\247\222)", nullptr));
        label_wave->setText(QCoreApplication::translate("monitorServerMainWindow", "~", nullptr));
        startBtn->setText(QCoreApplication::translate("monitorServerMainWindow", "\345\220\257\345\212\250\346\234\215\345\212\241\345\231\250", nullptr));
        statLabel->setText(QCoreApplication::translate("monitorServerMainWindow", "\345\234\250\347\272\277\345\256\242\346\210\267\347\253\257\357\274\2320", nullptr));
    } // retranslateUi

};

namespace Ui {
    class monitorServerMainWindow: public Ui_monitorServerMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONITORSERVERMAINWINDOW_H
