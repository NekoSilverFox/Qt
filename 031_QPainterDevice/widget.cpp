#include "widget.h"
#include "ui_widget.h"
#include <QPainter>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    /// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ QPixmap @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    /* QPixmap 不仅仅可以作为显示图片，也可以作为绘图设备（画纸） */
    QPixmap pix(300, 300);  // 画纸大小
    pix.fill(Qt::white);  // 设置默认填充色

    QPainter painter(&pix);  // 添加画家，并给他画纸
    painter.setPen(QPen(QColor(0, 255, 0)));
    painter.drawEllipse(QPoint(150, 150), 100, 100);

    pix.save("/Users/fox/雪狸的文件/Programma/Qt/031_QPainterDevice/res_pix.png");  // 保存到磁盘



}

Widget::~Widget()
{
    delete ui;
}

