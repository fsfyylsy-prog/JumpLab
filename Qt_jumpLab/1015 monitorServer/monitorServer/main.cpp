#include "monitorservermainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("JumpLab");
    a.setApplicationDisplayName("JumpLab 服务端");
    a.setApplicationVersion("1.0.0");

    monitorServerMainWindow w;
    w.show();
    return a.exec();
}
