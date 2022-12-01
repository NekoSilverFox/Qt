#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ List Widget @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    /* List Widget 接受一个 QListWidgetItem */
    QListWidgetItem* item = new QListWidgetItem("我是一行文字");
    item->setTextAlignment(Qt::AlignHCenter);  // 设置为 QListWidgetItem 中的文字居中对齐
    ui->listWidget->addItem(item);


    /* 如果想让 List Widget 一次性接受多个项，可以使用 QStringList，QstringList 类似于 QList<QString>，有自己重载的 `<<` 运算符 */
    QStringList stringList;
    stringList << "赤橙黄绿青蓝紫" << "谁持彩练当空舞" << "雨后复斜阳" << "关山阵阵苍";
    ui->listWidget->addItems(stringList);  // 【重点】函数是 addItem`S`


    /* 使用匿名对象 */
    ui->listWidget->addItems(QStringList() << "Do not go gentle into that good night"
                                           << "Old age should burn and rave at close of day"
                                           << "Rage, rage against the dying of the light");



    // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Tree Widget @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    /* 1. 设置 `Tree Widget` 的头（顶端的标签） */
    ui->treeWidget->setHeaderLabels(QStringList() << "品种" << "说明");

    /* 2. 添加顶层项目 */
    QTreeWidgetItem* twiCat = new QTreeWidgetItem(QStringList() << "猫");
    QTreeWidgetItem* twiDog = new QTreeWidgetItem(QStringList() << "狗");
    QTreeWidgetItem* twiFox = new QTreeWidgetItem(QStringList() << "狐");


    /* 3. 将顶层项目添加到 `Tree Widget` */
    ui->treeWidget->addTopLevelItem(twiCat);
    ui->treeWidget->addTopLevelItem(twiDog);
    ui->treeWidget->addTopLevelItem(twiFox);


    /* 4. 为顶层项目添加子项目（孩子） */
    QTreeWidgetItem* orangeCat = new QTreeWidgetItem(QStringList() << "橘猫" << "橙色的猫");
    QTreeWidgetItem* blackCat = new QTreeWidgetItem(QStringList() << "橘猫" << "黑色的猫");
    QTreeWidgetItem* russiaCat = new QTreeWidgetItem(QStringList() << "俄罗斯猫" << "爱喝伏特加的猫");

    twiCat->addChild(orangeCat);  // 第一种方式，一次只添加一个
    twiCat->addChild(blackCat);
    twiCat->addChild(russiaCat);




}

Widget::~Widget()
{
    delete ui;
}

