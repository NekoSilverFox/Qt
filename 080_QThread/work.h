#ifndef WORK_H
#define WORK_H

#include <QObject>

class Work : public QObject
{
    Q_OBJECT
public:
    explicit Work(QObject *parent = nullptr);

    void someWork();

    /* 通过信号调用父对象的 ui 刷新 */
signals:
    void signalUupdateUI(unsigned int i);
};

#endif // WORK_H
