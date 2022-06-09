#include "widget.h"
#include <QPushButton>

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
//    connect(teacher, &Teacher::hungry,
//            student, &Student::treat);

    /* 【重点】
     * 有参的信号和槽的链接
     * 使用函数指针说明参数是什么，指向函数地址
    */
    void (Teacher::*pfunc_teacher) (QString) = &Teacher::hungry;
    void (Student::*pfunc_student) (QString) = &Student::treat;
    connect(teacher, pfunc_teacher,
            student, pfunc_student);

    /* 通过按钮使用信号和槽 | 信号连接信号再连接槽
     * 一旦进行了重载就要使用函数指针，以使 connect 知道要调用哪一个函数
     */
    QPushButton* btn = new QPushButton("下课啦", this);
    this->resize(600, 400);
    void (Teacher::*pfunc_teacher_void) (void) = &Teacher::hungry;
    void (Student::*pfunc_student_void) (void) = &Student::treat;
    connect(btn, &QPushButton::clicked,
            teacher, pfunc_teacher_void);  // 信号连接信号，将按钮点击连接到老师饿了
    connect(teacher, pfunc_teacher_void,
            student, pfunc_student_void);  // 信号连接槽，将老师饿了的信号连接至学生请客


    /* 信号和槽是可以断开的 */
//    disconnect(teacher, pfunc_teacher_void,
//              student, pfunc_student_void);

    /*【重点】
     * 一个信号可以连接多个槽
     * 多个信号是可以连接同一个槽函数
     * 信号和槽函数的参数类型必须一一对应，但信号的参数个数可以大于槽函数（反之不可以）
     */
    QPushButton* btn2 = new QPushButton("按钮 2", this);
    btn2->move(100, 0);
    connect(btn2, &QPushButton::clicked,
            this, &Widget::close);


    /* 链接之后还是不够的，要将触发老师饿了的信号 */
    classOver();
}

void Widget::classOver()
{
    // 触发自动以的老师饿了的信号
    // 【重点】触发自定义信号的关键字为 `emit`
    emit teacher->hungry();

    emit teacher->hungry("红烧肉");

}

Widget::~Widget()
{
}

