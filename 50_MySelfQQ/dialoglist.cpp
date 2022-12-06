#include "dialoglist.h"
#include "ui_dialoglist.h"
#include "widget.h"

#include <QPushButton>
#include <QMessageBox>

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
        vIsOpen.push_back(false);

        ui->vLayout->addWidget(btn); // 加到垂直布局中
    }


     /* 对 9 个按钮添加信号和槽 */
    for (auto i = 0; i < vToolBtn.size(); i++)
    {
        /* 弹出聊天对话框 */
        connect(vToolBtn.at(i), &QToolButton::clicked,
                this,
                [=](){

                        /* 如果窗口已经被打开，就不要再执行 */
                        if (true == vIsOpen.at(i))
                        {
                            QMessageBox::warning(this, "警告", QString("%1 的窗口已经被打开了").arg(vToolBtn.at(i)->text()));
                            return;
                        }

                        Widget* widget = new Widget(nullptr, vToolBtn.at(i)->text());  // nullptr 代表为顶层窗口，参数二为构建窗口时告诉与某人的聊天窗口
                        widget->setWindowTitle(vToolBtn.at(i)->text());
                        widget->setWindowIcon(QIcon(":/nekosilverfox.png"));
                        widget->show();

                        vIsOpen[i] = true;


                        /* 关闭聊天对话框 重置是否打开的数组 */
                        connect(widget, &Widget::signalClose,
                                this, [=](){
                                            vIsOpen[i] = false;
                        });
        });

    }
}

DialogList::~DialogList()
{
    delete ui;
}
