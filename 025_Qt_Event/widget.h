#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


    /* 定时器事件 */
    void timerEvent(QTimerEvent* event);

private:
    Ui::Widget *ui;

    /* 定时器 id 编号 */
    int timer_id1;
    int timer_id2;
};
#endif // WIDGET_H
