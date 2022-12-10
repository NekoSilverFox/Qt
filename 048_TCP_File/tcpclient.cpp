#include "tcpclient.h"
#include "ui_tcpclient.h"

TCPClient::TCPClient(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TCPClient)
{
    ui->setupUi(this);
}

TCPClient::~TCPClient()
{
    delete ui;
}

