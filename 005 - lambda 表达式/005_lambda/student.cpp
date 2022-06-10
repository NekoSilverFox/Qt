#include "student.h"
#include <QDebug>

Student::Student(QObject *parent)
    : QObject{parent}
{

}

void Student::treat()
{
    qDebug() << "学生请老师吃饭了";
}

void Student::treat(QString food_name)
{
    // 【重点】将 QString 先转 utf8 (QByteArray)，再转成 char*
    qDebug() << "学生请老师吃" << food_name.toUtf8().data();
}
