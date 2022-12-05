#include "dialoglist.h"
#include "ui_dialoglist.h"

#include <QToolButton>

DialogList::DialogList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DialogList)
{
    ui->setupUi(this);

    /* 窗口操作 */
    setWindowTitle("MySelfQQ-Silverfox");  // 设置标题
    setWindowIcon(QIcon(":/nekosilverfox.png"));  // 设置图标

    /* 测试数据 */
    QStringList nameList;
    nameList << "冰糖雪狸" << "奇迹" << "玄狸" << "诺瓦" << "小虎" << "书齐" << "张三" << "罗翔" << "罗永浩" << "罗振宇";

    /* 用容器保存住按钮，方便后续操作 */
    QVector<QToolButton*> vToolBtn;

    for (auto i : nameList)
    {
        /* 设置头像 */
        QToolButton* btn = new QToolButton;
        btn->setText(i);
        btn->setIcon(QIcon(":/user-group.png"));
        btn->setAutoRaise(true);  // 按钮透明风格
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);  // 设置显示图标和文字
        btn->setFixedSize(220, 50);

        vToolBtn.push_back(btn);

        ui->vLayout->addWidget(btn); // 加到垂直布局中
    }
}

DialogList::~DialogList()
{
    delete ui;
}
