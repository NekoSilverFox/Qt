#ifndef TCPSERVERWIDGET_H
#define TCPSERVERWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>

namespace Ui {
class TcpServerWidget;
}

class TcpServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpServerWidget(QWidget *parent = 0);
    ~TcpServerWidget();

private slots:
    void on_buttonFile_clicked();

    void on_buttonSend_clicked();

private:
    Ui::TcpServerWidget *ui;

    QTcpServer *tcpServer; //监听套接字
    QTcpSocket *tcpSocket; //通信套接字

    QString fileName;//文件名字
    qint64 fileSize;//文件大小
    qint64 sendSize;//已经发了多少数据

    //文件对象
    QFile file;

    //发送数据的函数
    void sendDate();

    QTimer *myTimer;
};

#endif // TCPSERVERWIDGET_H
