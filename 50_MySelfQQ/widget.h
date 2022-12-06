#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent, QString userName);
    ~Widget();

    virtual void closeEvent(QCloseEvent*);  // 【重写】触发关闭事件

signals:
    void signalClose();  // 【自定义信号】如果关闭窗口则发送关闭信号

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
