#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 调用自定义控件的自定义接口
    connect(ui->btnGetValue, &QPushButton::clicked,
            [=](){qDebug() << "值：" << ui->widget->getValue();});  //【重点】这里的 ui->widget 就是我们的自定义控件

    connect(ui->btnSetHalf, &QPushButton::clicked,
            [=](){ui->widget->setValue(50);});
}

Widget::~Widget()
{
    delete ui;
}

