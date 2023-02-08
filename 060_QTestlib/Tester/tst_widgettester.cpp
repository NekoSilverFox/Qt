#include <QtTest>  // 单元测试必须包含，但是包含后会拖慢编译速度。因为他们包含了所有模块。注意不要写成 QtTest！

// add necessary includes here
#include <QLineEdit>
#include <QPushButton>

#include "../App/widget.h"


class WidgetTester : public QObject
{
    Q_OBJECT

public:
    WidgetTester();
    ~WidgetTester();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();
    void testGui();
    void testSingal();
};

WidgetTester::WidgetTester()
{

}

WidgetTester::~WidgetTester()
{

}

void WidgetTester::initTestCase()
{

}

void WidgetTester::cleanupTestCase()
{

}

void WidgetTester::test_case1()
{
    QCOMPARE("冰糖雪狸", "冰糖雪狸");
}

/** 测试 GUI（包含了获取 private 成员的方法）
 * @brief WidgetTester::testGui
 */
void WidgetTester::testGui()
{
    Widget widget;
    QLineEdit* lineEdit = widget.findChild<QLineEdit*>("lineEdit");  // 【重点】获取 private 成员的方法

    QTest::keyClicks(lineEdit, "Hellooooooo");  // 但是不知道为什么，如果换成中文就报错

    QCOMPARE(lineEdit->text(), QString("Hellooooooo"));
}

/** 测试信号
 * @brief WidgetTester::testSingal
 */
void WidgetTester::testSingal()
{
    Widget widget;
    QPushButton* pushButton = widget.findChild<QPushButton*>("pushButton");

    QSignalSpy spy(pushButton, &QPushButton::clicked);
//    pushButton->animateClick();  // 做一些触发信号的事情
    pushButton->click();
    QCOMPARE(spy.count(), 1);  // 确保信号被准确地发射了一次

    QList<QVariant> arguments = spy.takeFirst(); // take the first signal
    QVERIFY(arguments.at(0).toBool() == false);   // 验证第一个参数

}










//QTEST_APPLESS_MAIN(WidgetTester)
QTEST_MAIN(WidgetTester)  // 自动为我们创建用于测试的 main 函

#include "tst_widgettester.moc"  // 编译或者生成一个额外的 cpp 文件，其中包含您需要的所有元结构 (因为 Qt 的信号和槽不属于 C++标准的内容)。以进行Qt的内省工作
