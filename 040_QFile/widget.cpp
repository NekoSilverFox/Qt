#include "widget.h"
#include "ui_widget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QTextCodec>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    /* 点击按钮 选取文件 */
    connect(ui->btnOpenFile, &QPushButton::clicked,
            this, [=](){

        QString path = QFileDialog::getOpenFileName(this, "打开文件", ".", "*.txt");

        if (path.isEmpty())
        {
            QMessageBox::critical(this, "错误", "打开失败！");
        }
        else
        {
            ui->leFilePath->setText(path);  // 如果选择了文件，就把路径写入到 LineEdit

            /* 读取文件 */
            QFile file(path);  // QFile 默认读取 UTF-8
            file.open(QIODevice::ReadOnly);  // 也可以使用它的子类：QFileDevice::ReadOnly

#if 0
            /* 一行一行的读 */
            QByteArray byteArray;
            while (!file.atEnd())
            {
                byteArray += file.readLine();
            }
#endif

            /* 一次性读取 */
            QByteArray byteArray = file.readAll();  // 读取全部数据

            /* 加载到文本编辑框 */
            ui->textEdit->setText(byteArray);
            // ui->textEdit->setText(QTextCodec::codecForName("gbk")->toUnicode(byteArray));  // 读取 GBK 格式

            /* 【重点】使用完别忘记关闭 */
            file.close();


            /// @@@@@@@@@@@@@@@@@@@@@@@ 写文件 @@@@@@@@@@@@@@@@@@@@@@@
            file.open(QFileDevice::Append);  // 重新指定打开方式，我们要追加一行话
            file.write("冰糖雪狸！！！");
            file.close();
        }
    });
}

Widget::~Widget()
{
    delete ui;
}

