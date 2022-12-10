#include "tcpserverwidget.h"
#include "tcpclientwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpServerWidget w;
    w.show();

    TcpClientWidget w2;
    w2.show();

    return a.exec();
}
