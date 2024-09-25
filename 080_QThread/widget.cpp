#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(100);

    /* 初始化两个对象 */
    work = new Work();  // 注意，这里 work 一定不能传入父对象！！否则无法调用线程！！
    thread = new QThread(this);

    /* 将工作对象移动到线程中 */
    work->moveToThread(thread);
    connect(thread, &QThread::started, work, &Work::someWork);
    connect(ui->btnStart, &QPushButton::clicked, this, [=](){ thread->start();});    // 点击按钮启动线程
    connect(ui->btnStop, &QPushButton::clicked, this, [=](){ thread->terminate();});  // 直接中断线程，但不建议使用这个函数

    /* 主线程接收并处理另一个线程执行过程中发出的信号 */
    connect(work, &Work::signalUupdateUI, this, &Widget::updateUI, Qt::QueuedConnection);

}

Widget::~Widget()
{
    if (thread->isRunning()) {
        thread->quit();    // 退出线程
        thread->wait();    // 等待线程完成
    }
    delete work;
    delete thread;

    delete ui;
}

void Widget::updateUI(unsigned int i)
{
    ui->textBrowser->append(QString::number(i));
    ui->progressBar->setValue(i % 101);
}

