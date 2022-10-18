#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->actionNewFile->setIcon(QIcon(":/fox_black_ground"));
    ui->actionEditFile->setIcon(QIcon(":/Picture/nekosilverfox.png"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

