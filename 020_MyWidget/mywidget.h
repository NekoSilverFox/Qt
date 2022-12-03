#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

namespace Ui {
class MyWidget;
}

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

    // 自定义接口
    void setValue(const int value);
    int getValue();

private:
    Ui::MyWidget *ui;
};

#endif // MYWIDGET_H
