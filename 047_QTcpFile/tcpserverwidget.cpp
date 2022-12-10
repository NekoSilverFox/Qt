#include "tcpserverwidget.h"
#include "ui_tcpserverwidget.h"
#include <QFileInfo>
#include <QFileDialog>
#include <QFile>

#define cout qDebug() << "[" << __FILE__ <<":" << __LINE__ << "]"

TcpServerWidget::TcpServerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServerWidget)
{
    ui->setupUi(this);
    setWindowTitle("服务器端口：8888");

    //两个按钮都不能按
    ui->buttonFile->setEnabled(false);
    ui->buttonSend->setEnabled(false);

    //监听套接字
    tcpServer=new QTcpServer(this);

    //监听
    tcpServer->listen(QHostAddress::Any,8888);

    connect(tcpServer,&QTcpServer::newConnection,
            [=](){
                    //取出建立好连接的套接字
                    tcpSocket=tcpServer->nextPendingConnection();

                    //获取对方的IP和端口
                    QString ip=tcpSocket->peerAddress().toString();
                    qint16 port =tcpSocket->peerPort();
                    QString ipDate=QString("[ip=%1 port=%2] 建立好连接了！！").arg(ip).arg(port);

                    ui->textEdit->append(ipDate);
                    ui->buttonFile->setEnabled(true);
                }

            );

    myTimer=new QTimer(this);
    connect(myTimer,&QTimer::timeout,
                [=](){
                         //关闭定时器
                         myTimer->stop();

                         //发送文件
                         sendDate();
                    }

                );
}

TcpServerWidget::~TcpServerWidget()
{
    delete ui;
}

//打开文件 获取文件的基本信息
void TcpServerWidget::on_buttonFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
                                    this,tr("Open File"),"../"
                                    );
    //cout<<filePath;

    fileName.clear();
    fileSize=0;

    //获取文件的基本信息
    //QFileInfo获取文件信息
    QFileInfo FileDate(filePath);
    //qDebug()<<FileDate.exists();
    if(FileDate.exists()){
        qDebug() << "文件名字：" <<FileDate.fileName();
        qDebug() << "文件大小：" << FileDate.size()<<"bit";
        fileName=FileDate.fileName();
        //cout<<fileName;
        fileSize=FileDate.size();
        //cout<<fileSize;
      }

    //打开文件
    if(!filePath.isEmpty()){
        //只读方式打开文件
        //指定文件的名字
        file.setFileName(filePath);

        //打开文件
        bool openOk=file.open(QIODevice::ReadOnly);
        if(openOk){
            //提示打开文件的路径
            ui->textEdit->append("文件打开成功了。");
        }
        else{
            cout<<"文件打开失败了。";
        }
    }

    ui->buttonFile->setEnabled(false);
    ui->buttonSend->setEnabled(true);

}

//先发送文件信息 再发送数据
void TcpServerWidget::on_buttonSend_clicked()
{
    //文件信息先发送 “fileName_fileSize”
    QString head=QString("%1**%2").arg(fileName).arg(fileSize);
    //给对方发送数据， 使用套接字是tcpSocket
    //cout<<head;
    qint64 len;
    len=tcpSocket->write(head.toUtf8().data());
    //发送成功了
    if(len>0){
        //再发送数据
        //发送真正的文件信息
        //防止TCP黏包
        //需要通过定时器延时 20 ms
        myTimer->start(20);
    }
    else{
        //如果发送失败
        file.close();
        ui->buttonFile->setEnabled(true);
        ui->buttonSend->setEnabled(false);
    }
}

void TcpServerWidget::sendDate(){
    ui->textEdit->append("正在发送数据");
    qint64 len=0;
    sendSize=0;

    do{
        //每次发送数据的大小
        char buf[4*1024] = {0};
        len = 0;

        //往文件中读数据
        len = file.read(buf, sizeof(buf));
        //cout<<len;
        //发送数据，读多少，发多少
        len=tcpSocket->write(buf,len);
        //cout<<len;

        //发送的数据需要累积
        sendSize += len;
        cout<<"sendSize="<<sendSize;
    }while(len>0);
    //cout<<"是否发送文件完毕";

    //cout<<"sendSize="<<sendSize;
    //cout<<"fileSize"<<fileSize;
    //是否发送文件完毕
    if(sendSize==fileSize){
        ui->textEdit->append("数据发送完毕");
        file.close();
        //主动和客户端端口连接
        tcpSocket->disconnectFromHost();
        tcpSocket->close();
        tcpSocket = NULL;
    }
}
