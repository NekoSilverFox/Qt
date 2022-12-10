#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>


#include <QTcpSocket>
#include <QTcpServer>
#include <QFile>
#include <QTime>


namespace Ui {
class TCPServer;
}

class TCPServer : public QWidget
{
    Q_OBJECT

public:
    explicit TCPServer(QWidget *parent = nullptr);
    ~TCPServer();

private:
    Ui::TCPServer *ui;

    QTcpSocket* tcpSocket;  // 监听套接字
    QTcpServer* tcpServer;  // 通信套接字

    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 bytesAlreadySend;  // 已经发了多少数据

    QTimer* timer;

    void sendFile();
};

#endif // TCPSERVER_H
