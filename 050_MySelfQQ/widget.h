#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUdpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    enum MsgType {Msg, UserJoin, UserLeft};

public:
    Widget(QWidget *parent, QString userName);
    ~Widget();

    void sendMsg(MsgType type);  // 广播 UDP 消息
    void userJoin(QString name);  // 处理用户加入
    void userLeft(QString name, QString time);  // 处理用户离开
    QString getUser();  // 获取用户名
    QString getMsg();  // 获取聊天信息

    virtual void closeEvent(QCloseEvent*);  // 【重写】触发关闭事件

signals:
    void signalClose();  // 【自定义信号】如果关闭窗口则发送关闭信号

private:
    Ui::Widget *ui;

    QUdpSocket* udpSocket;  // UDP 套接字
    qint16 port;  // 端口
    QString userName;  // 用户名

    void receiveMessage();  // 接收 UDP 消息

};
#endif // WIDGET_H
