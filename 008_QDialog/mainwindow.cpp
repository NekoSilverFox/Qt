#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDialog>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /** Dialog 对话框有两种：
     *  - 模态对话框：    在[栈]上创建，对话框弹出之后会通过 `.exec()` 阻塞，无法操作其他窗口
     *  - 非模态对话框：  在[堆]上创建，对话框通过 `.show()` 弹出，弹出后依旧可以操作其他窗口
     *
     *  这里 我们使用 Lambda 表达式的形式弹出 Dialog对话框，并连接信号和槽
     */
    connect(ui->actionopenDialog, &QAction::triggered,
            this, [=](){
                    #if 0
                            /* 模态对话框 */
                            QDialog dialog_1(this);
                            dialog_1.resize(80, 60);
                            dialog_1.exec();  // 阻塞
                    #endif

                            /* 非模态对话框 */
                            QDialog* dialog_2 = new QDialog(this);  // 创建到堆上，不然 Lambda 表达式结束就会给释放了（窗口一闪而过）
                            dialog_2->resize(100, 80);
                            dialog_2->setAttribute(Qt::WA_DeleteOnClose);  // 【重点】设置 Dialog 对话框在关闭时释放内存！如果不设置只会在 MainWindow 退出时才释放，这可能造成内存泄漏
                            dialog_2->show();


                            qDebug() << "Lambda 表达式内部";
    }); // END_LAMBDA

//========================================================================================================================

    /* 标准对话框 QMessageBox 介绍（Static 成员）：*/
    connect(ui->actionQMessageBox, &QAction::triggered,
            this, [=](){
        QMessageBox::about(this, "static QMessageBox::about 函数", "text部分"); // 会弹出一段文字
        QMessageBox::aboutQt(this, "title部分");  // 会弹出 Qt 的声明

        QMessageBox::critical(this, "[Title]错误！", "[Text]critical");        // 错误对话框
        QMessageBox::warning(this, "[Title]警告！", "[Text]warning");          // 警告对话框
        QMessageBox::information(this, "[Title]信息！", "[Text]information");  // 信息对话框

        /* 询问对话框
         * 参数：1. 父亲，2. 标题，3.提示内容， 4. 按键类型， 5. 关联回车按键（默认按哪个）
         */
        if (QMessageBox::Save ==
                QMessageBox::question(this, "问题", "question", QMessageBox::Save | QMessageBox::Cancel, QMessageBox::Cancel))
        {
            qDebug() << "按键是 QMessageBox::Save";
        }
        else
        {
            qDebug() << "按键类型是 QMessageBox::Cancel";
        }


    }); // END_LAMBDA

    //======================================================颜色对话框==================================================================
    connect(ui->actionColor, &QAction::triggered,
            this, [](){
                            QColor color = QColorDialog::getColor(QColor(0, 255, 255));
                            qDebug() << "选择的颜色为：" << color.red() << color.green() << color.blue();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

