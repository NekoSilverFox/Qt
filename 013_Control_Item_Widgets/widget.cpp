#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>


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



    // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Table Widget @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    /* 1. 设置列数 */
    QStringList listHead;
    listHead << "姓名" << "性别" << "年龄";
    ui->tableWidget->setColumnCount(listHead.size());

    /* 2. 设置水平头 */
    ui->tableWidget->setHorizontalHeaderLabels(listHead);

    /* 3. 行数 */
    ui->tableWidget->setRowCount(5);

    /* 4. 设置正文 */
    QStringList listName;
    listName << "爱迪生" << "居里" << "特斯拉";

    QList<QString> listSex;
    listSex << "男" << "女" << "男";

    for (int row = 0; row < listName.size(); row++)
    {
        int col = 0;
        ui->tableWidget->setItem(row, col, new QTableWidgetItem(listName[row]));
        col++;

        ui->tableWidget->setItem(row, col, new QTableWidgetItem(listSex.at(row)));  // 【复习】.at(i) 越界会抛出异常，[i] 会直接挂掉
        col++;

        ui->tableWidget->setItem(row, col, new QTableWidgetItem(QString::number(row + 40))); // 【重点】注意 数字转 QString 的方法
    }

    /* 点击按钮添加霍金 */
    connect(ui->btnAddHuoJin, &QPushButton::clicked,
            this, [=](){
        bool isEmpty = ui->tableWidget->findItems("霍金", Qt::MatchExactly).empty();  // 因为返回的是一个 List，如果没有则 List 为 empty

        if (isEmpty)
        {
            ui->tableWidget->insertRow(0); // 线插入新的行（行号）
            ui->tableWidget->setItem(0, 0, new QTableWidgetItem("霍金"));
            ui->tableWidget->setItem(0, 1, new QTableWidgetItem("男"));
            ui->tableWidget->setItem(0, 2, new QTableWidgetItem("77"));
        }
        else
        {
            QMessageBox::warning(this, "警告！！", "霍金已存在于 Table Widget");  // 【复习】标准提示框是 static 方法
        }
    });

    /* 点击按钮删除霍金 */
    connect(ui->btnDelHuoJin, &QPushButton::clicked,
            this, [=](){
        QList<QTableWidgetItem*> resFind = ui->tableWidget->findItems("霍金", Qt::MatchExactly); // findItems 返回的是一个 QList

        if (resFind.empty())
        {
            QMessageBox::warning(this, "你找茬？", "霍金已经不在了！！！");
        }
        else
        {
            ui->tableWidget->removeRow(resFind.first()->row());  // 【根据行号删除】根据结果第一行的行号删除
        }
    });

}

Widget::~Widget()
{
    delete ui;
}

