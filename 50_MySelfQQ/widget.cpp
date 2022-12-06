#include "widget.h"
#include "ui_widget.h"
#include <QDataStream>
#include <QDateTime>

Widget::Widget(QWidget *parent, QString userName)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->udpSocket = new QUdpSocket(this);
    this->userName = userName;  // 获取用户名
    this->port = 8888;  // 端口号

    this->udpSocket->bind(this->port,  // 绑定端口号
                          QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);  // 共享地址 + 断线重连

    // 创建新窗口就相当于新用户进入
    sendMsg(MsgType::UserJoin);

    /* 点击发送按钮发送消息 */
    connect(ui->btnSend, &QPushButton::clicked,
            [=](){sendMsg(MsgType::Msg);});

    /* 接收（监听）消息 */
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Widget::receiveMessage);
}

Widget::~Widget()
{
    delete ui;
}

/* 触发关闭事件 */
void Widget::closeEvent(QCloseEvent*)
{
    emit this->signalClose();
}

/* 广播 UDP 消息 */
void Widget::sendMsg(MsgType type)
{
    /** 消息分为 3 类，所以要对数据做分段处理
    *   第一段：数据类型
    *   第二段：用户名
    *   第二段：具体内容
    */

    QByteArray byteArray;
    QDataStream dataStream(&byteArray, QIODevice::WriteOnly);

    dataStream << type;       // 数据块1：消息类型
    dataStream << getUser();  // 数据块2：用户名

    /* 添加消息块2 的内容 */
    switch (type) {
    case Msg:
        if (ui->msgTextEdit->toPlainText().isEmpty()) return;
        dataStream << getMsg();
        break;

    case UserJoin:

        break;

    case UserLeft:
        break;

    default:
        break;
    }

    /* 开始书写报文 */
    udpSocket->writeDatagram(byteArray,
                             QHostAddress(QHostAddress::Broadcast),  // 广播及断线重连
                             port);
}


/* 接收和解析 UDP 消息 */
void Widget::receiveMessage()
{
    /* 拿到数据报文 */
    qint64 size = udpSocket->pendingDatagramSize();
    QByteArray array = QByteArray(size, 0);
    udpSocket->readDatagram(array.data(), size);

    /* 解析数据 */
    MsgType msgType;
    QString name;
    QString msg;
    QDataStream dataStream(&array, QIODevice::ReadOnly);
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");

    dataStream >> msgType;
    dataStream >> name;
    dataStream >> msg;
    qDebug() << msgType << name << msg;

    switch (msgType) {
    case Msg:
        // 追加聊天记录
        ui->msgBrowser->setTextColor(Qt::blue);
        ui->msgBrowser->append("[" + name + "] " + time);
        ui->msgBrowser->append(msg);
        break;

    default:
        break;
    }


}


/* 获取聊天信息 */
QString Widget::getMsg()
{
    QString str = ui->msgTextEdit->toHtml();

    // 顺便清空对话框
    ui->msgTextEdit->clear();
    ui->msgTextEdit->setFocus();

//    qDebug() << str;
    return str;
}

/* 获取用户名 */
QString Widget::getUser()
{
    return this->userName;
}
