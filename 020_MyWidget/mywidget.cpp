#include "mywidget.h"
#include "ui_mywidget.h"

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    /* QSpinBox变化， Silder 移动 */
    void(QSpinBox:: * mySpinBoxSignal)(int) = &QSpinBox::valueChanged; // 由于存在重载，所以要使用函数指针，避免调用不明确
    connect(ui->spinBox, mySpinBoxSignal,
            ui->horizontalSlider, &QSlider::setValue);

    /* Silder 移动,QSpinBox变化 */
    connect(ui->horizontalSlider, &QSlider::valueChanged,
            ui->spinBox, &QSpinBox::setValue);

}


// 自定义接口
void MyWidget::setValue(const int value)
{
    ui->spinBox->setValue(value);
}


int MyWidget::getValue()
{
    return ui->spinBox->value();
}

MyWidget::~MyWidget()
{
    delete ui;
}
