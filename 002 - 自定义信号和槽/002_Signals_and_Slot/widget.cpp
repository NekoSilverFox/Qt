#include "widget.h"

/**
 * 需求：
 *  创建两个类 Teacher 和 Student
 *  下课后，老师发送一个信号 —— 饿了
 *  然后学生使用一个槽函数 —— 请老师吃饭
 * @brief Widget::Widget
 * @param parent
 */

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    student = new Student(this);  // 【重点】因为 Student 的父类是 QObject，所以这里的 this 是将 Student 添加到对象树中，以便之后 Qt 自动释放
    teacher = new Teacher(this);

    /* 链接老师发出的信号和学生的槽函数 */
    connect(teacher, &Teacher::hungry,
            student, &Student::treat);

    /* 链接之后还是不够的，要将触发老师饿了的信号 */
    classOver();
}

void Widget::classOver()
{
    // 触发自动以的老师饿了的信号
    // 【重点】触发自定义信号的关键字为 `emit`
    emit teacher->hungry();

}

Widget::~Widget()
{
}

