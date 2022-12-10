#include "clienttcp.h"
#include "ui_clienttcp.h"
#include <QHostAddress>

ClientTCP::ClientTCP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientTCP)
{
    ui->setupUi(this);
    setWindowTitle("客户端");

    tcpSocket=new QTcpSocket(this);

    connect(tcpSocket,&QTcpSocket::connected,
            [=](){
                    ui->textEditRead->setText("与服务端已经成功连接!");
                 }

            );

    //从通信套接字里面取内容
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=](){
                    //获取对方发送的内容
                    QByteArray array = tcpSocket->readAll();
                    //追加到编辑区中
                    ui->textEditRead->append(array);
                 }

            );

}

ClientTCP::~ClientTCP()
{
    delete ui;
}

void ClientTCP::on_buttonConnect_clicked()
{
    //获取服务器ip和端口
    QString ip=ui->lineEditIP->text();
    qint16 port=ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void ClientTCP::on_buttonWrite_clicked()
{
    //获取编辑器内容，发送到套接字
    //获取编辑区内容
    QString str=ui->textEditWrite->toPlainText();
    //给对方发送数据， 使用套接字是tcpSocket
    tcpSocket->write(str.toUtf8().data());
}

void ClientTCP::on_buttonClose_clicked()
{
    //主动和客户端端口连接
    tcpSocket->disconnectFromHost();
    tcpSocket->close();

}


