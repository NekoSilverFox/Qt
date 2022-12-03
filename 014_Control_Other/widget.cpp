#include "widget.h"
#include "ui_widget.h"
#include <QMovie>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    /* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Stacked Widget @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
    // 点击按钮 Stacked Widget 切换页
    connect(ui->btnScrollArea, &QPushButton::clicked,
            this, [=](){ui->stackedWidget->setCurrentIndex(0);}); //  Scroll Area

    connect(ui->btnToolBox, &QPushButton::clicked,
            this, [=](){ui->stackedWidget->setCurrentIndex(1);}); //  Tool Widget

    connect(ui->btnTabWidget, &QPushButton::clicked,
            this, [=](){ui->stackedWidget->setCurrentIndex(2);}); //  Tab Widget

    // 设置默认选中第 0 项
    ui->stackedWidget->setCurrentIndex(0);


    /* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Combo Box - 下拉框 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
    ui->comboBox->addItem("狐狸");  // 添加值
    ui->comboBox->addItem("狗子");
    ui->comboBox->addItem("猫子");

//    connect(ui->btnSelectCat, &QPushButton::clicked,
//            this, [=](){ui->comboBox->setCurrentIndex(2);});  // 通过按钮选择

    connect(ui->btnSelectCat, &QPushButton::clicked,
            this, [=](){ui->comboBox->setCurrentText("猫子");});  // 通过按钮选择


    /* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Dial - 滚轮 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
    ui->dial->setMaximum(0);  // 设置最小最大值
    ui->dial->setMaximum(365);
    connect(ui->dial, &QDial::valueChanged,
            this, [=](int value){ qDebug() << "Dial value: " << value;});  // 如果指针位置变化就输出数值

    /* @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Label - 显示图片 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ */
     ui->labelPic->setPixmap(QPixmap(":/pic/nekosilverfox.png"));  // 显示图片
     ui->labelPic->setScaledContents(true);  // 设置自动缩放到可用空间

     // 显示动图
     QMovie* movie = new QMovie(":/pic/舔屏.gif");
     ui->labelGif->setMovie(movie);
     ui->labelGif->setScaledContents(true);
     movie->start(); // 播放



}

Widget::~Widget()
{
    delete ui;
}

