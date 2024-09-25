#include "work.h"
#include <QDebug>
#include <QThread>

Work::Work(QObject *parent)
    : QObject{parent}
{}

/**
 * @brief Work::someWork 这个类只做计算，并将计算结果通过信号的方式发送到主线程
 * 此函数模拟一些耗时的算法
 */
void Work::someWork()
{
    unsigned int i = 0;
    while (true)
    {
        emit signalUupdateUI(i);
        qDebug() << i;
        i++;

        QThread::msleep(10);
    }
}
