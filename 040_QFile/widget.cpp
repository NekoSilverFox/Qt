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

            /// @@@@@@@@@@@@@@@@@@@@@@@ 通过 QFileInfo 读取文件信息 @@@@@@@@@@@@@@@@@@@@@@@
            QFileInfo info(path);
            ui->lbPath->setText(info.filePath());
            ui->lbName->setText(info.fileName());
            ui->lbSize->setText(QString("%1 Kb").arg(info.size()));
            ui->lbSuffix->setText(info.suffix());
            ui->lbCreateTime->setText(QString("创建日期：%1").arg(info.birthTime().toString("yyyy-MM-dd hh:mm:ss")));
            ui->lbModifTime->setText(QString("修改时间：%1").arg(info.lastModified().toString("yyyy/MM/dd hh:mm:ss")));

        }
    });

    /**
     * 文件流读写文件
     * 分类：
     *    - 文本流（基础数据类型）
     *    - 数据流（大型 QImage）
     **/
    /*@@@@@@@@@@@@@@@@@@@@@@@ 文本流 @@@@@@@@@@@@@@@@@@@@@@@*/
    QFile file("aaa.txt");
    file.open(QIODevice::WriteOnly);

    QTextStream textStream(&file);
    textStream << "冰糖 雪狸" << 123456789;  // 写入
    file.close();

    file.open(QIODevice::ReadOnly);  // 读取
    QString str;
    textStream >> str;  // 【重点】这种方式遇到空格结束！
    qDebug() << str;
    qDebug() << textStream.readAll();  // 读取【剩下的】所有
    file.close();


    /*@@@@@@@@@@@@@@@@@@@@@@@ 数据流 @@@@@@@@@@@@@@@@@@@@@@@*/
    QFile dataFile("bbb.txt");
    dataFile.open(QIODevice::WriteOnly);

    QDataStream dataStream(&dataFile);  //【重点】数据流写入的是二进制文件块，而不是明文！
    dataStream << "冰糖 雪狸" << 987654;  //【重点】数据流-QDataStream 写入的数据块！！比如这里写入的是 "冰糖 雪狸" 和 987654两个数据块
    dataFile.close();

    dataFile.open(QIODevice::ReadOnly);

    QString strBlock;
    int num;
    dataStream >> strBlock >> num;  // 【重点】读取数据块！！
    qDebug() << strBlock << num;
    dataFile.close();


}

Widget::~Widget()
{
    delete ui;
}

