#ifndef UDP_2_H
#define UDP_2_H

#include <QWidget>
#include <QUdpSocket>

namespace Ui {
class Udp_2;
}

class Udp_2 : public QWidget
{
    Q_OBJECT

public:
    explicit Udp_2(QWidget *parent = nullptr);
    ~Udp_2();

private:
    Ui::Udp_2 *ui;

public:
    QUdpSocket* udp;  // 套接字（一个套接字就是网络上进程通信的一端）
};

#endif // UDP_2_H
