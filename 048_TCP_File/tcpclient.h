#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QWidget>

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
};
#endif // TCPCLIENT_H
