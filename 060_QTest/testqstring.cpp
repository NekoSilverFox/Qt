#include "testqstring.h"


void TestQString::initTestCase()
{
    qDebug() << "开始执行单元测试";
}


void TestQString::to_upper()
{
    QString str = "Hello";
    QVERIFY(str.toUpper() == "HELLO");
}


void TestQString::cleanupTestCase()
{
    qDebug() << "单元测试全部测试结束";
}
