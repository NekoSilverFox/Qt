#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>  // 坐标轴
#include <QtCharts/QScatterSeries>

// 引用命名空间
// QT_CHARTS_USE_NAMESPACE  这个宏在 Qt 6 中不再被支持
// using namespace QtCharts;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void timerStart();
    void timerStop();

    void drawPoint();

private:
    Ui::Widget *ui;

    QChart* chart;
    QSplineSeries *splineSeries;
    QScatterSeries* scatterSeries;
    QValueAxis *axisX;
    QValueAxis *axisY;

    QTimer* timer;
};
#endif // WIDGET_H
