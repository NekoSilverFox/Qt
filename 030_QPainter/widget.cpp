#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QTimer>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    posX = 0;

    /* 随着时间往右移动图片 */
    QTimer* timerMovePic = new QTimer(this);
    timerMovePic->start(100);
    connect(timerMovePic, &QTimer::timeout,
            [=](){
            posX += 10;
            update();   // 记得使用 update 重新绘制，就像 OpenGL
    });

}

Widget::~Widget()
{
    delete ui;
}


/* QPainter，不需要手动调用。系统自己会调用。并且我们的 Widget 也可以充当绘图窗口（画纸） */
void Widget::paintEvent(QPaintEvent *)
{
    /* 1.创建画家，并且指定绘图设备 */
    QPainter painter(this);

    /* 2.设置笔的风格（设置风格一定要在使用笔之前） */
    QPen pen(QColor(255, 0, 255));
    pen.setWidth(3);  // 笔的宽度
    pen.setStyle(Qt::DotLine);  // 笔的风格

    /* 设置画刷（对于封闭图形的填充） */
    QBrush brush(Qt::cyan);
    brush.setStyle(Qt::Dense3Pattern);

    /* 3.让画家用这个笔 */
    painter.setPen(pen);
    painter.setBrush(brush);

    /* 4.让画家画画 */
    painter.drawLine(QPoint(0, 0), QPoint(100, 100));  // 线
    painter.drawEllipse(QPoint(100, 100), 100, 50);  // 椭圆
    painter.drawRect(QRect(QPoint(10, 10), QPoint(50, 50)));  // 矩形
    painter.drawText(QRect(10, 200, 150, 50), "我是文本框中的一段文字");  // 字体

    /* 绘制图片 */
    if (posX > 300) posX = 0;  // 超出边界移回来
    painter.drawPixmap(posX, 150, QPixmap(":/pic/nekosilverfox.png"));
}
