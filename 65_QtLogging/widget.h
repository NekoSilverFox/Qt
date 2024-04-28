#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class widget; }
QT_END_NAMESPACE

class widget : public QWidget
{
    Q_OBJECT

public:
    widget(QWidget *parent = nullptr);
    ~widget();

    void onDebug();
    void onInfo();
    void onWarning();
    void onCritical();
    void onFatal();

private:
    Ui::widget *ui;
};
#endif // WIDGET_H
