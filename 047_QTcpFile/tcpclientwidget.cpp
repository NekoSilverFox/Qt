#include "tcpclientwidget.h"
#include "ui_tcpclientwidget.h"
#include <QMessageBox>
#include <QHostAddress>

#define cout qDebug() << "[" << __FILE__ <<":" << __LINE__ << "]"

TcpClientWidget::TcpClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpClientWidget)
{
    ui->setupUi(this);
    setWindowTitle("客户端");
    startInfo=true;

    tcpSocket=new QTcpSocket(this);

    ui->progressBar->setValue(0); //当前值

    connect(tcpSocket,&QTcpSocket::connected,
            [=](){
                    ui->textEdit->setText("与服务端已经成功连接!");
                 }

            );

    //从通信套接字里面取内容
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=](){
                    //获取对方发送的内容
                    QByteArray array = tcpSocket->readAll();

                    if(startInfo){
                        startInfo=false;
                        receSize=0;
                        //字符串切割“fileName_fileSize”
                        QString temp=QString(array);
                        //文件名
                        fileName = QString(array).section("**", 0, 0);
                        fileSize = QString(array).section("**", 1, 1).toInt();

                        //指定文件的名字
                        file.setFileName(fileName);

                        //打开文件
                        bool openOk=file.open(QIODevice::WriteOnly);
                        if(!openOk){
                            cout<<"文件打开失败";
                            tcpSocket->disconnectFromHost(); //断开连接
                            tcpSocket->close(); //关闭套接字

                            return; //如果打开文件失败，中断函数
                        }

                        ui->progressBar->setMinimum(0);
                        ui->progressBar->setMaximum(fileSize/1024);
                        ui->progressBar->setValue(0); //当前值

                    }
                    else{
                        //是文件内容

                        qint64 len = file.write(array);
                        if(len>0){
                            receSize+=len;
                        }

                        //更新进度条
                        ui->progressBar->setValue(receSize/1024);

                        if(receSize==fileSize){
                            ui->textEdit->append("文件接收完成");
                            QMessageBox::information(this, "完成", "文件接收完成");

                            tcpSocket->disconnectFromHost(); //断开连接
                            tcpSocket->close(); //关闭套接字
                            file.close(); //关闭文件
                        }
                    }

                 }

            );
}

TcpClientWidget::~TcpClientWidget()
{
    delete ui;
}

//与服务器建立连接
void TcpClientWidget::on_buttonConnect_clicked()
{
    //获取服务器ip和端口
    QString ip=ui->lineEditIP->text();
    qint16 port=ui->lineEditPort->text().toInt();

    //主动和服务器建立连接
    tcpSocket->connectToHost(QHostAddress(ip),port);
}
