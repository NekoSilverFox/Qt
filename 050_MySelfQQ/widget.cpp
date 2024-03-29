#include "widget.h"
#include "ui_widget.h"
#include <QDataStream>
#include <QDateTime>
#include <QColorDialog>

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

    /* 点击退出按钮，关闭窗口 */
    connect(ui->btnExit, &QPushButton::clicked,
            this, [=](){this->close();});

    //////////////////////////////////////////////// 辅助功能 ////////////////////////////////////////////////
    /* 字体 */
    connect(ui->fontCbx, &QFontComboBox::currentFontChanged,
            [=](const QFont& font){
        ui->msgTextEdit->setCurrentFont(font);
        ui->msgTextEdit->setFocus();
    });

    /* 字号 */
    void(QComboBox::* cbxSingal)(const QString &text) = &QComboBox::currentTextChanged;
    connect(ui->cbxFontSize, cbxSingal,
            [=](const QString &text){
        ui->msgTextEdit->setFontPointSize(text.toDouble());
        ui->msgTextEdit->setFocus();
    });

    /* 加粗 */
    connect(ui->btnBlod, &QToolButton::clicked,
            [=](bool isCheck){
        if (isCheck) ui->msgTextEdit->setFontWeight(QFont::Bold);
        else ui->msgTextEdit->setFontWeight(QFont::Normal);
    });

    /* 倾斜 */
    connect(ui->btnItalic, &QToolButton::clicked,
            [=](bool isCheck){
        ui->msgTextEdit->setFontItalic(isCheck);
    });


    /* 下划线 */
    connect(ui->btnUnderLine, &QToolButton::clicked,
            [=](bool isCheck){
        ui->msgTextEdit->setFontUnderline(isCheck);
    });

    /* 更改颜色 */
    connect(ui->btnColor, &QToolButton::clicked,
            [=](){
        QColor color = QColorDialog::getColor(Qt::black);
        ui->msgTextEdit->setTextColor(color);
    });
}

Widget::~Widget()
{
    delete ui;
}

/* 触发关闭事件 */
void Widget::closeEvent(QCloseEvent* event)
{
    emit this->signalClose();
    sendMsg(MsgType::UserLeft);
    udpSocket->close();  // 关闭套接字
    udpSocket->destroyed();
    QWidget::closeEvent(event);
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

    switch (msgType) {
    case Msg:
        dataStream >> msg;

        // 追加聊天记录
        ui->msgBrowser->setTextColor(Qt::blue);
        ui->msgBrowser->append("[" + name + "] " + time);
        ui->msgBrowser->append(msg);
        break;

    case UserJoin:
        userJoin(name);
        break;

    case UserLeft:
        userLeft(name, time);
        break;

    default:
        break;
    }


}

/* 处理用户加入 */
void Widget::userJoin(QString name)
{
    if (ui->usrTbWidget->findItems(name, Qt::MatchExactly).isEmpty())
    {
        /* 更新用户列表 */
        QTableWidgetItem* user = new QTableWidgetItem(name);
        ui->usrTbWidget->insertRow(0);
        ui->usrTbWidget->setItem(0, 0, user);

        /* 追加聊天记录 */
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->append(QString("%1 上线了！").arg(name));

        /* 在线用户更新 */
        ui->lbNumberOnlineUser->setText(QString("在线用户：%1").arg(ui->usrTbWidget->rowCount()));

        /* 把自身信息广播 */
        sendMsg(UserJoin);
    }
}


/* 处理用户离开 */
void Widget::userLeft(QString name, QString time)
{
    if (!ui->usrTbWidget->findItems(name, Qt::MatchExactly).isEmpty())
    {
        /* 更新用户列表 */
        ui->usrTbWidget->removeRow(ui->usrTbWidget->findItems(name, Qt::MatchExactly).first()->row());

        /* 追加聊天记录 */
        ui->msgBrowser->setTextColor(Qt::gray);
        ui->msgBrowser->append(QString("%1 在 %2 离开了").arg(name).arg(time));

        /* 在线用户更新 */
        ui->lbNumberOnlineUser->setText(QString("在线用户：%1").arg(ui->usrTbWidget->rowCount()));

        /* 把自身信息广播 */
        sendMsg(UserJoin);
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
