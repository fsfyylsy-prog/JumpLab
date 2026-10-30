#include "monitorclientmainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("JumpLab");
    a.setApplicationDisplayName("JumpLab 客户端");
    a.setApplicationVersion("1.0.0");

    monitorClientMainWindow w;
    w.show();
    return a.exec();
}
