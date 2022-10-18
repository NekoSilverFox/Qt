#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->resize(600, 400);

    /* 菜单栏 */
    QMenuBar* menuBar = this->menuBar();  // 菜单栏只能有一个
    this->setMenuBar(menuBar); // 将菜单栏放入到窗口中

        /* 菜单 */
        QMenu* menuFile = menuBar->addMenu("文件");  // 创建菜单
        QMenu* menuEdit = menuBar->addMenu("编辑");

            /* 菜单项 */
            QAction* actionNewFile = menuFile->addAction("新建文件");  // 添加菜单项
            menuFile->addSeparator();  // 添加分隔线
            QAction* actionOpenFile = menuFile->addAction("打开文件");




    /* 工具栏 - 可以有多个 */
    QToolBar* toolBar = new QToolBar(this);          // 1. 创建一个工具栏
    this->addToolBar(Qt::LeftToolBarArea, toolBar);  // 2. 添加工具栏到当前窗口，并且设置默认停靠位置为左侧

    toolBar->addAction(actionNewFile);           // 3. 为工具栏添加项
    toolBar->addSeparator();                     // 添加分隔线
    toolBar->addAction(actionOpenFile);

    toolBar->setAllowedAreas(Qt::LeftToolBarArea | Qt::BottomToolBarArea);   // （可选）设置工具栏允许的停靠位置
    toolBar->setMovable(true);                   // 【总开关】开启或者关闭工具栏的可【移动性】
    toolBar->setFloatable(false);                // 设置可【浮动性】为否



}

MainWindow::~MainWindow()
{
}

