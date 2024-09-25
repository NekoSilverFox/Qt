#ifndef WIDGET_H
#define WIDGET_H

#include "work.h"

#include <QWidget>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void updateUI(unsigned int i);

private:
    Ui::Widget *ui;

    QThread* thread; // 线程对象，计算任务会在在这个线程执行
    Work* work;      // 包含耗时操作的对象
};
#endif // WIDGET_H
