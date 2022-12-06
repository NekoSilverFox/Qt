#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent, QString userName)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
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
