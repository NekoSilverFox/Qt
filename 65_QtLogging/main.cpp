#include "widget.h"
#include <QApplication>
#include <QDir>
#include <QLoggingCategory>


int main(int argc, char *argv[])
{
    QLoggingCategory::setFilterRules("*.debug=false;");  // 设置日志级别

    QApplication a(argc, argv);

    qDebug() << "This debug message should not be shown.";
    qInfo() << "This info message will be shown.";

    widget w;
    w.show();

    return a.exec();
}
