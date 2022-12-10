#include "tcpserver.h"
#include "ui_tcpserver.h"

#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>

TCPServer::TCPServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCPServer)
{
    ui->setupUi(this);

    this->setWindowTitle("服务器端口：2333");

    /* 点击选择文件按钮 */
    connect(ui->btnSelectFile, &QPushButton::clicked,
            [=](){
        QString path = QFileDialog::getOpenFileName(this, "Open file", ".");
        if (path.isEmpty())
        {
            QMessageBox::warning(this, "Warning", "Send Cancel, you have not selected any files");
            ui->textEdit->setTextColor(Qt::darkYellow);
            ui->textEdit->append("[WARNING] Send Cancel");
            return;
        }

        QFileInfo info(path);
        this->fileName = info.fileName();
        this->fileSize = info.size();  // bytes
        this->file.setFileName(path);
        bool isOpenSucc = this->file.open(QIODevice::ReadOnly);
        if (isOpenSucc)
        {
            ui->textEdit->setTextColor(Qt::blue);
            ui->textEdit->append(QString("[INFO] File opened successfully\n"
                                          "Path: %1\n"
                                          "Size: %2Kb").arg(path).arg(fileSize / 1024));
        }
        else
        {
            ui->textEdit->setTextColor(Qt::red);
            ui->textEdit->append("[ERROR] File opening failed");
            return;
        }

    });

    /* 监听套接字 */
    this->tcpServer = new QTcpServer(this);
    this->tcpServer->listen(QHostAddress::Any, 2333);
    connect(tcpServer, &QTcpServer::newConnection,
            this, [=](){
        this->tcpSocket = tcpServer->nextPendingConnection();  // 将下一个挂起的连接作为已连接的QTcpSocket对象返回

        /* 记录 Client 信息 */
        QString clientIp = tcpSocket->peerAddress().toString();
        qint16 clientPort = tcpSocket->peerPort();

        ui->textEdit->setTextColor(Qt::blue);
        ui->textEdit->append(QString("[INFO] Success connected to %1:%2 ").arg(clientIp).arg(clientPort));
    });

    /* 发送完文件头之后，每隔固定时间发送一个数据包 */
    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout,
            [=](){
        timer->stop();
        sendFile();
    });

    /* 点击发送按钮，先发送文件信息再发送数据 */
    connect(ui->btnSendFile, &QPushButton::clicked,
            [=](){
        QByteArray      headerByteArray;   // 先发送 header
        QDataStream     dataStream(&headerByteArray, QIODevice::WriteOnly);

        dataStream << this->fileName;             // header第1段：文件名（QString）
        dataStream << this->fileSize;             // header第2段：文件大小（qint64）

        qint64 len = tcpSocket->write(headerByteArray);

        /* 如果header发送成功了，再发送数据。 并且为了防止TCP黏包，需要通过定时器延时 20 ms*/
        if (len > 0)
        {
            timer->start(20);
            return;
        }
        else
        {
            file.close();
            ui->textEdit->setTextColor(Qt::red);
            ui->textEdit->append("[ERROR] File header sending failed");
            return;
        }
    });


}

TCPServer::~TCPServer()
{
    delete ui;
}

void TCPServer::sendFile()
{
    ui->textEdit->setTextColor(Qt::blue);
    ui->textEdit->append("[INFO] Sending data...");

    qint64 lenPackage = 0;  // 记录[当前]数据包大小
    this->bytesAlreadySend = 0;

    do {
        lenPackage = 0;
        char buf[4 * 1024] = {0};  // 【数据包】每次发送的数据
        lenPackage = file.read(buf, lenPackage);
        lenPackage = tcpSocket->write(buf, lenPackage);  // 发送数据，读多少，发多少

        this->bytesAlreadySend += lenPackage;  // 发送的数据需要累积
        qDebug() << "this->bytesAlreadySend: " << this->bytesAlreadySend;

    } while (lenPackage > 0);

    if (this->bytesAlreadySend == this->fileSize)
    {
        ui->textEdit->setTextColor(Qt::green);
        ui->textEdit->append("[INFO] Success to send file\n---------------------------\n");
        this->file.close();
        this->tcpSocket->disconnectFromHost();
        this->tcpSocket->close();
        this->tcpSocket = nullptr;
    }

    return;
}
