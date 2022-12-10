#include "tcpclient.h"
#include "tcpserver.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TCPServer server;
    server.show();

//    TCPClient w;
//    w.show();
    return a.exec();
}
