#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>


class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

    /* 重写虚函数：鼠标进入 */
    void enterEvent(QEnterEvent*);

    /* 重写虚函数：鼠标离开 */
    void leaveEvent(QEvent*);

    /* 重写虚函数：鼠标移动 */
    virtual void mouseMoveEvent(QMouseEvent *event);

    /* 重写虚函数：鼠标点击 */
    virtual void mousePressEvent(QMouseEvent *event);

    /* 重写虚函数：鼠标释放 */
    virtual void mouseReleaseEvent(QMouseEvent *event);

    /* 事件拦截 */
    virtual bool event(QEvent* event);

signals:



};

#endif // MYLABEL_H
