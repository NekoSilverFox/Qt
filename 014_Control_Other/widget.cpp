#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 点击按钮 Stacked Widget 切换页
    connect(ui->btnScrollArea, &QPushButton::clicked,
            this, [=](){ui->stackedWidget->setCurrentIndex(0);}); //  Scroll Area

    connect(ui->btnToolBox, &QPushButton::clicked,
            this, [=](){ui->stackedWidget->setCurrentIndex(1);}); //  Tool Widget

    connect(ui->btnTabWidget, &QPushButton::clicked,
            this, [=](){ui->stackedWidget->setCurrentIndex(2);}); //  Tab Widget

    // 设置默认选中第 0 项
    ui->stackedWidget->setCurrentIndex(0);

}

Widget::~Widget()
{
    delete ui;
}

