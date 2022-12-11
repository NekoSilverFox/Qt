#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class TCPClient; }
QT_END_NAMESPACE

class TCPClient : public QWidget
{
    Q_OBJECT

public:
    TCPClient(QWidget *parent = nullptr);
    ~TCPClient();

private:
    Ui::TCPClient *ui;

    QTcpSocket* tcpSocket;  // 监听套接字

    QFile file;  //文件对象
    QString fileName;
    qint64 fileSize;

    bool isHeaderReceived;  // 判断是否是接收到文件头
    qint64 bytesReceived;   // 已经发了多少数据

};
#endif // TCPCLIENT_H
