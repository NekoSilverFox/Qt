#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPicture>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    /// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ QPixmap @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    /* QPixmap 不仅仅可以作为显示图片，也可以作为绘图设备（画纸），对不同平台做优化 */
    QPixmap pix(300, 300);  // 画纸大小
    pix.fill(Qt::white);  // 设置默认填充色

    QPainter painter(&pix);  // 添加画家，并给他画纸
    painter.setPen(QPen(QColor(0, 255, 0)));
    painter.drawEllipse(QPoint(150, 150), 100, 100);

    pix.save("/Users/fox/雪狸的文件/Programma/Qt/031_QPainterDevice/res_pix.png");  // 保存到磁盘


    /// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ QImage @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    /* QImage 作为绘图设备，对不同像素级做优化。可以修改像素点 */
    QImage image(300, 300, QImage::Format_RGB32);
    image.fill(Qt::white);

    QPainter painter2(&image);
    painter2.setPen(QPen(QColor(255, 255, 0)));
    painter2.drawRect(20, 20, 250, 250);
    image.save("/Users/fox/雪狸的文件/Programma/Qt/031_QPainterDevice/res_pix.png");


    /// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ QPicture @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//    /* QPicture 作为绘图设备，用于记录、重现绘图【指令】 */
//    QPicture pic;
//    QPainter painter3;

//    painter3.begin(&pic); // 开始记录绘图指令

//    painter.setPen(QPen(QColor(255, 0, 0)));
//    painter.drawEllipse(QPoint(150, 150), 50, 50);

//    painter3.end(); // 结束记录绘图指令
//    pic.save("/Users/fox/雪狸的文件/Programma/Qt/031_QPainterDevice/pic.command"); // 保存绘图指令
}

Widget::~Widget()
{
    delete ui;
}

// 绘图事件
void Widget::paintEvent(QPaintEvent* event)
{
    QImage img;
    img.load(":/nekosilverfox.png");

    /* 对像素做修改 */
    for (int i = 100; i < 200; i++)
    {
        for (int j = 100; j < 200; j++)
        {
//            QRgb value = qRgb(255, 0, 0);
            img.setPixel(QPoint(i, j), Qt::red);
        }
    }

    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), img);

    /// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ QPicture @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    /// 重现绘图指令
    QPicture pic;
    bool isSucc = pic.load("/Users/fox/雪狸的文件/Programma/Qt/031_QPainterDevice/pic.command");
    qDebug() << isSucc;
    painter.drawPicture(QPoint(0, 0), pic);
}
