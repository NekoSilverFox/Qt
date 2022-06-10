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
     * 使用函数指针说明参数是什么，指向函数地址 ↓
    */
    void (Teacher::*pfunc_teacher) (QString) = &Teacher::hungry;
    void (Student::*pfunc_student) (QString) = &Student::treat;
    connect(teacher, pfunc_teacher,
            student, pfunc_student);

    /* 通过按钮使用信号和槽 | 信号连接信号再连接槽
     * 一旦进行了重载就要使用函数指针，以使 connect 知道要调用哪一个函数
     */
    QPushButton* btn = new QPushButton("下课啦", this);
    this->resize(600, 400);  // 以构造函数指定父类的，需要调整下窗口大小，避免窗口过小
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
    connect(btn, &QPushButton::clicked,
            this, &Widget::close);

    QPushButton* btn2 = new QPushButton("按钮 2", this);
    btn2->move(100, 0);
    connect(btn2, &QPushButton::clicked,
            this, &Widget::close);





    /*【重点】Qt4 之下信号和槽的写法
     * 优点：
     *  - 参数类型比较直观，发生重载也不需要函数指针
     *
     * 缺点:
     *  - 参数的匹配不会进行检测
     *  - 不检测的原因：SIGNAL() 和 SLOT() 下会把里面的带代码作为字符串处理
    */
    connect(teacher, SIGNAL(hungry(QString)),
            student, SLOT(treat(QString)));


    /* 链接之后还是不够的，要将触发老师饿了的信号 */
    classOver();





    // == == == == == == == == == == == == == == == == == == == == == == == ==
    /*【重点】lambda 表达式 */
    QPushButton* btn3 = new QPushButton;
    btn3->setText("测试 lambda");
    btn3->move(300, 0);
    btn3->setParent(this);

    /*【重点】
     * [](){} 仅仅是 lambda 表达式的声明
     * [](){}() 才是调用 lambda 表达式
     */
    [=](){btn3->setText("lambda 改名惹");}();  // 注意最后加上括号才是进行调用

    /* mutlable 关键字进行 const 值拷贝 */
    QPushButton * myBtn = new QPushButton ("mutable", this);
    QPushButton * myBtn2 = new QPushButton ("无 mutable", this);
    myBtn2->move(100,100);
    int m = 10;

    // lambda 如果使用值传递，那么值传递的变量在 lambda 中都会变成 const，所以如果想在 lambda 中对值修改，要加 mutable 关键字
    // 此时的 mutable 是进行了拷贝，不影响外部的！
    //                                              ↓ mutable 关键字
    connect(myBtn,&QPushButton::clicked,this,[m] ()mutable { m = 100 + 10; qDebug() << m; });
    // connect(myBtn,&QPushButton::clicked,this,[m] () { m = 100 + 10; qDebug() << m; });
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

