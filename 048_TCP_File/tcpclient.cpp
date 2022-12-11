#include "tcpclient.h"
#include "ui_tcpclient.h"

#include <QMessageBox>
#include <QFileDialog>

TCPClient::TCPClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TCPClient)
{
    ui->setupUi(this);

    this->setWindowTitle("Client");

    this->tcpSocket = new QTcpSocket(this);

    /* 点击连接按钮，与服务器建立连接 */
    connect(ui->btnConnect, &QPushButton::clicked, [=](){
        /* 用户指定保存路径 */
//        savePath = QFileDialog::getSaveFileName(this, "Save file to", "");
//        if (savePath.isEmpty())
//        {
//            QMessageBox::warning(this, "Warning", "Save cancel");
//            return;
//        }
//        ui->textBrowser->setTextColor(Qt::blue);
//        ui->textBrowser->append(QString("[INFO] The file will save to path: %1").arg(savePath));
       this->isHeaderReceived = false;
       QString serverIp = ui->leServerIp->text();
       qint16 serverPort = ui->leServerPort->text().toInt();
       this->tcpSocket->connectToHost(QHostAddress(serverIp), serverPort);  // 服务器建立连接
    });

    /* 点击断开连接按钮 */
    connect(ui->btnDisconnect, &QPushButton::clicked, [=](){
        tcpSocket->disconnectFromHost(); //断开连接
        tcpSocket->close(); //关闭套接字
    });



    /* 如果与主机建立连接 */
    connect(this->tcpSocket, &QTcpSocket::connected,
            [=](){
        ui->textBrowser->setTextColor(Qt::green);
        ui->textBrowser->append("[INFO] Successfully establish a link with the host");
    });

    /* 如果与主机断开连接 */
    connect(this->tcpSocket, &QTcpSocket::disconnected,
            [=](){
        ui->textBrowser->setTextColor(Qt::darkYellow);
        ui->textBrowser->append("[WARRING] Disconnected with the host");
    });

    /* 从通信套接字里面取内容 */
    connect(tcpSocket, &QTcpSocket::readyRead, [=](){
        /* 读取数据 */
//        qint64 dataSize = tcpSocket->readBufferSize();
//        if (0 == dataSize)
//        {
//            ui->textBrowser->setTextColor(Qt::red);
//            ui->textBrowser->append("[ERROR] Receiving interruption: Unable to read file information");
//            return;
//        }
//        QByteArray byteArray = QByteArray(dataSize, 0);
//        byteArray = tcpSocket->readAll();
        QByteArray byteArray = tcpSocket->readAll();
        ui->textBrowser->append(QString("[INFO] bytesReceived: %1").arg(bytesReceived));


        /* 如果是文件头 */
        if (!isHeaderReceived)
        {
            ui->textBrowser->setTextColor(Qt::blue);
            ui->textBrowser->append("[INFO] Start parsing the data");

            this->isHeaderReceived = true;
            this->bytesReceived = 0;
            ui->progressBar->setValue(0);

            /** 解析 header
            *   header第1段：文件名（QString）
            *   header第2段：文件大小（qint64）
            */

            QDataStream dataStream(&byteArray, QIODevice::ReadOnly);
            dataStream >> this->fileName;             // header第1段：文件名（QString）
            dataStream >> this->fileSize;             // header第2段：文件大小（qint64）
            ui->textBrowser->append(QString("[INFO] File info:\n"
                                    "Name: %1\n"
                                    "Size: %2Kb").arg(fileName).arg(fileSize / 1024));


            this->file.setFileName(QString("/Users/fox/Desktop/" + this->fileName));
            bool isFileOpen = file.open(QIODevice::WriteOnly);
            if (!isFileOpen)
            {
                ui->textBrowser->setTextColor(Qt::red);
                ui->textBrowser->append("[ERROR] Can not write to file");
                tcpSocket->disconnectFromHost(); //断开连接
                tcpSocket->close(); //关闭套接字
                return;
            }
            ui->textBrowser->setTextColor(Qt::blue);
            ui->textBrowser->append(QString("[INFO] The file will save to path: %1").arg(file.fileName()));
        }
        /* 文件头接收，接下来是文件的数据内容 */
        else
        {
            qint64 lenWrite = file.write(byteArray);
            if (lenWrite > 0) this->bytesReceived += lenWrite;
            qDebug() << "Client 已经接收：" << bytesReceived;

            ui->progressBar->setValue(bytesReceived / fileSize * 100);  // 更新进度条

            if (fileSize == bytesReceived)
            {
                ui->textBrowser->setTextColor(Qt::green);
                ui->textBrowser->append(QString("[INFO] File received successfully, already saved to the path: %1").arg(fileName));

                this->isHeaderReceived = false;
                this->bytesReceived = 0;

                tcpSocket->disconnectFromHost(); //断开连接
                tcpSocket->close(); //关闭套接字
                file.close(); //关闭文件
                return;
            }
        }
    });
}

TCPClient::~TCPClient()
{
    delete ui;
}

