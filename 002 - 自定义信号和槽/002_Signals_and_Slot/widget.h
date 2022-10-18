#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "student.h"
#include "teacher.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void classOver();  // 下课 —— 用于触发信号和槽
    ~Widget();

    /* 之所以将对象在这里创建，是为了让 Widget 全局都可以访问到（作用域） */
    Student* student;
    Teacher* teacher;


    /* 测试键盘响应事件 */
    void keyPressEvent(QKeyEvent* event);
};
#endif // WIDGET_H
