#include <QtTest>  // 单元测试必须包含，但是包含后会拖慢编译速度。因为他们包含了所有模块。注意不要写成 QtTest！

// add necessary includes here

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

void WidgetTester::testGui()
{
    QCOMPARE("冰糖雪狸", "冰糖雪狸");
}

QTEST_APPLESS_MAIN(WidgetTester)
//QTEST_MAIN(HelloTest)  // 自动为我们创建用于测试的 main 函

#include "tst_widgettester.moc"  // 编译或者生成一个额外的 cpp 文件，其中包含您需要的所有元结构 (因为 Qt 的信号和槽不属于 C++标准的内容)。以进行Qt的内省工作
