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
    this->resize(600, 400);

    student = new Student(this);  // 【重点】因为 Student 的父类是 QObject，所以这里的 this 是将 Student 添加到对象树中，以便之后 Qt 自动释放
    teacher = new Teacher(this);


    /* 【重点】
     * 有参的信号和槽的链接
     * 使用函数指针说明参数是什么，指向函数地址 ↓
    */
    void (Teacher::*pfunc_teacher) (QString) = &Teacher::hungry;
    void (Student::*pfunc_student) (QString) = &Student::treat;
    connect(teacher, pfunc_teacher,
            student, pfunc_student);


    // == == == == == == == == == == == == == == == == == == == == == == == ==
    /*【重点】lambda 表达式 */
    QPushButton* btn3 = new QPushButton;
    btn3->setText("测试 lambda");
    btn3->move(300, 200);
    btn3->setParent(this);

    /*【重点】
     * [](){} 仅仅是 lambda 表达式的声明
     * [](){}() 才是调用 lambda 表达式
     */
    [=](){btn3->setText("lambda 改名惹");}();  // 注意最后加上括号才是进行调用，前面加上 `=` 才能调用 this 中的变量

    /* mutlable 关键字进行 const 值的拷贝 */
    QPushButton * myBtn = new QPushButton ("mutable", this);
    QPushButton * myBtn2 = new QPushButton ("无 mutable", this);
    myBtn2->move(100,0);
    int m = 10;

    // lambda 如果使用值传递，那么值传递的变量在 lambda 中都会变成 const，所以如果想在 lambda 中对值修改，要加 mutable 关键字
    // 此时的 mutable 是进行了拷贝，不影响外部的！
    //                                              ↓ mutable 关键字
    connect(myBtn,&QPushButton::clicked,this,[m] ()mutable { m = 100 + 10; qDebug() << m; });
    // connect(myBtn,&QPushButton::clicked,this,[m] () { m = 100 + 10; qDebug() << m; });  // ERROR
    connect(myBtn2,&QPushButton::clicked,this,[=] ()  { qDebug() << m; });
    qDebug() << m;



    /* lambda 返回值 */
    int tmp = []() -> int {return 696969;}();  // 注意最后加括号进行调用
    qDebug() << tmp;





    /* 做信号和槽连接，默认内部变量是加锁的，也就是只读状态，如果在内部进行修改，那么会报错 */
//    connect(btn3, &QPushButton::clicked,
//            this, [&](){
//        btn3->setText("mutable 叒改名惹！");
//    });





    /* 无参按钮调用 有参请客吃饭 */
    connect(btn3, &QPushButton::clicked,
            this, [=](){teacher->hungry("糖醋里脊1");});  // OK

    connect(btn3, &QPushButton::clicked,
            teacher, [=](){teacher->hungry("糖醋里脊2");});  // OK

    connect(btn3, &QPushButton::clicked,
            [=](){teacher->hungry("糖醋里脊3");});  // OK

//    connect(btn3, &QPushButton::clicked,
//            teacher, teacher->hungry("糖醋里脊4"));  // ERROR

    /* 点击按钮 关闭窗口 */
    connect(btn3, &QPushButton::clicked,
            this, [=](){this->close();});
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

