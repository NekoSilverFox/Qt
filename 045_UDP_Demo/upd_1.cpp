#include "upd_1.h"
#include "ui_upd_1.h"
#include <QUdpSocket>

Upd_1::Upd_1(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Upd_1)
{
    ui->setupUi(this);

    /* 初始化属性 */
    ui->lbMyPort->setText("8888");
    ui->lb2Port->setText("9999");
    ui->lb2IP->setText("127.0.0.1");

    udp = new QUdpSocket(this);  // 创建套接字
    udp->bind(ui->lbMyPort->text().toInt());  // 绑定自身端口号

    /* 点击发送按钮，发送数据（报文） */
    connect(ui->btnSend, &QPushButton::clicked,
            this, [=](){
        // 书写报文：参数1：内容；     参数2：对方IP；   参数3：对方端口
        udp->writeDatagram(ui->teInput->toPlainText().toUtf8(),
                           QHostAddress(ui->lb2IP->text()),
                           ui->lb2Port->text().toInt());
        ui->teRecord->append("My say: " + ui->teInput->toPlainText());  // 把自己写的内容写到聊天框
        ui->teInput->clear();  // 清空输入框
    });

    /* 接收数据 */
    connect(udp, &QUdpSocket::readyRead,
            this, [=](){
        qint64 dataSize = udp->pendingDatagramSize();  // 获取报文长度
        QByteArray data = QByteArray(dataSize, 0);
        udp->readDatagram(data.data(), dataSize); // 读取报文
        ui->teRecord->append(data);  // 报文同步到聊天记录
    });
}

Upd_1::~Upd_1()
{
    delete ui;
}

