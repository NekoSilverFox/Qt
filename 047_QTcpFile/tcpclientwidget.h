#ifndef TCPCLIENTWIDGET_H
#define TCPCLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class TcpClientWidget;
}

class TcpClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpClientWidget(QWidget *parent = 0);
    ~TcpClientWidget();

private slots:
    void on_buttonConnect_clicked();

private:
    Ui::TcpClientWidget *ui;

    QTcpSocket *tcpSocket; //通信套接字

    QString fileName;//文件名字
    qint64 fileSize;//文件大小
    qint64 receSize;//已经收了多少数据

    bool startInfo;//判断是否是接收到文件信息了

    //文件对象
    QFile file;
};

#endif // TCPCLIENTWIDGET_H
