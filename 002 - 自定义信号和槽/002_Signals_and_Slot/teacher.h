#ifndef TEACHER_H
#define TEACHER_H

#include <QObject>

class Teacher : public QObject
{
    Q_OBJECT
public:
    explicit Teacher(QObject *parent = nullptr);

signals:
    /** 【重点】
     * 自定义的信号必须写在 signals 之下
     * 返回值的类型必须为 void
     * 信号只需要声明，不需要实现
     * 信号可以有参数，可以重载
     */
    void hungry();

    /* 重载 */
    void hungry(QString food_name);


};

#endif // TEACHER_H
