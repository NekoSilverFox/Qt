#include "widget.h"
#include "ui_widget.h"
#include <QTimerEvent>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    /* 启动定时器 */
    timer_id1 = this->startTimer(1000);  // 每 1000ms（1s），调用一次 timeEvent 事件
    timer_id2 = this->startTimer(2000);

    /* 定时器第二种方式（推荐） */
    QTimer* timer3 = new QTimer(this);
    timer3->start(500);  // 启动定时器
    connect(timer3, &QTimer::timeout,
            this, [=](){
        static int num3 = 0;
        ui->label_4->setText(QString::number(num3++));
    });

    /* 点击按钮暂停 */
     connect(ui->btnStop, &QPushButton::clicked,
             this, [=](){timer3->stop();});


}

Widget::~Widget()
{
    delete ui;
}

/* 定时器事件 */
void Widget::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == timer_id1)
    {
        static int num1 = 0;
        ui->label_2->setText(QString::number(num1++));
    }

    if (event->timerId() == timer_id2)
    {
        static int num2 = 0;
        ui->label_3->setText(QString::number(num2++));
    }
}
