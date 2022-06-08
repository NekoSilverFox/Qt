#ifndef STUDENT_H
#define STUDENT_H

#include <QObject>

class Student : public QObject
{
    Q_OBJECT
public:
    explicit Student(QObject *parent = nullptr);

signals:

public slots:
    /** 【重点】
     * 槽函数可以写在 `public slots` 之下，也可以写在 `public` 之下（仅限于高版本）
     * 槽函数的返回值类型为 void
     * 槽函数必须声明 + 实现
     * 参函数可以有参数，可以重载
     *
     */
    void treat();  // 请客

};

#endif // STUDENT_H
