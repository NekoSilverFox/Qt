#ifndef UPD_1_H
#define UPD_1_H

#include <QWidget>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Upd_1; }
QT_END_NAMESPACE

class Upd_1 : public QWidget
{
    Q_OBJECT

public:
    Upd_1(QWidget *parent = nullptr);
    ~Upd_1();

private:
    Ui::Upd_1 *ui;


public:
    QUdpSocket* udp;  // 套接字（一个套接字就是网络上进程通信的一端）
};
#endif // UPD_1_H
