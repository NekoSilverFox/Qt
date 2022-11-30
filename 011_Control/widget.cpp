#include "widget.h"
#include "ui_widget.h"
#include <QCheckBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->checkBox, &QCheckBox::stateChanged,
            this, [=](int state) {qDebug() << "QCheckBox state: " << state;});
}

Widget::~Widget()
{
    delete ui;
}

