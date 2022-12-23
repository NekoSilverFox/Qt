#include "widget.h"

#include <QApplication>

#include "testqstring.h"

int main(int argc, char *argv[])
{
    TestQString testQString;

    /* 调用 QTest::qExec(对象) 进行测试 */
    QTest::qExec(&testQString);
//    QTest::qExec(new TestQString);

    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
