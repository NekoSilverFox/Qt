#include "mylabel.h"
# include <QMouseEvent>

MyLabel::MyLabel(QWidget *parent)
    : QLabel{parent}
{
    this->setMouseTracking(true);  // 因为鼠标移动是一个连续的事件，而点击和释放是一个【瞬间】所以要实现鼠标不点击就跟踪，要开启这句
}

/* 重写虚函数：鼠标进入 */
void MyLabel::enterEvent(QEnterEvent*)
{
    qDebug() << "鼠标进入";
}

/* 重写虚函数：鼠标离开 */
void MyLabel::leaveEvent(QEvent*)
{
    qDebug() << "鼠标离开";
}

/* 重写虚函数：鼠标移动 */
void MyLabel::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)  // 【重点】因为鼠标移动是一个连续事件，左移要用 buttonS 而不是 button 并且要用 `&` 进行判断
        qDebug() << "鼠标[按住左键]移动了 - " << QString("鼠标当前位置 x: %1, y: %2").arg(event->x()).arg(event->y());

    qDebug() << "鼠标移动了 - " << QString("鼠标当前位置 x: %1, y: %2").arg(event->x()).arg(event->y());
}

/* 重写虚函数：鼠标点击 */
void MyLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        qDebug() << "鼠标[左键]点击了 - " << QString("鼠标当前位置 x: %1, y: %2").arg(event->x()).arg(event->y());
}

/* 重写虚函数：鼠标释放 */
void MyLabel::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "鼠标释放了 - " << QString("鼠标当前位置 x: %1, y: %2").arg(event->x()).arg(event->y());
}


/* 事件拦截 (鼠标点击) */
bool MyLabel::event(QEvent* event)
{
    /* 拦截鼠标[按下]事件，也就是不会调用上面写的函数了 */
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* mouseEv = static_cast<QMouseEvent*>(event);  // 【复习】将父类转换为子类
        qDebug() << "Event::鼠标[按下]了 - " << QString("鼠标当前位置 x: %1, y: %2").arg(mouseEv->x()).arg(mouseEv->y());
        return true;  // 返回 true 代表拦截
    }

    return QLabel::event(event);  // 其他事件，让父亲做默认处理
}

