#include "widget.h"
#include "mybutton.h"
#include <QPushButton>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)  // 将参数传给父类，让父类进行一个初始化
{
    /*按钮*/
    QPushButton* btn = new QPushButton;
    // btn->show();  // show 是顶层方式弹出，如果想在 Widget 窗口中显示，就需要依赖 Widget 窗口
    btn->setParent(this);  // 设置按钮他爹
    btn->setText("冰糖雪狸"); // 设置文字，将 char* 隐式转换为 QString


    /*创建按钮的第 2 种方式*/
    QPushButton* btn2 = new QPushButton("按钮 2", this);
    this->resize(600, 400);  // 重置窗口大小
    btn2->move(50, 50);  // 移动按钮
    btn2->resize(50, 50);  // 改变按钮大小


    /*窗口*/
    this->setWindowTitle("Qt第一个窗口");  // 窗口的标题
    this->setFixedSize(600, 400);  // 设置固定窗口大小

    /* Qt 在一定程度上简化了内内存的回收机制（对象树），也就是有时候不需要手动 Delete */
    MyButton* btn3 = new MyButton;
    btn3->setParent(this);
    btn3->setText("关闭窗口");
    btn3->move(100, 50);

    /*使用信号和槽机制通过点击按钮关闭窗口
        信号和槽：
        connect(信号的发送方, 信号的地址, 信号接收方, 动作-槽的地址)
    */
    connect(btn3, &MyButton::clicked,  // 其实是调用的父类的 QPushButton::clicked
            this, &Widget::close);


}

Widget::~Widget()
{
    qDebug() << "Widget 析构了";
}

