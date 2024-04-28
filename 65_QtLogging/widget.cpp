#include "widget.h"
#include "ui_widget.h"
#include "logger.h"

widget::widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::widget)
{
    ui->setupUi(this);

    Logger::init("/Users/fox/雪狸的文件/Programma/Qt/65_QtLogging/log", "yyyy-MM-dd hh:mm:ss", " | ");  // 初始化 Logger

    connect(ui->btnDebug, &QPushButton::clicked, this, &widget::onDebug);
    connect(ui->btnInfo, &QPushButton::clicked, this, &widget::onInfo);
    connect(ui->btnWarning, &QPushButton::clicked, this, &widget::onWarning);
    connect(ui->btnCritical, &QPushButton::clicked, this, &widget::onCritical);
    connect(ui->btnFatal, &QPushButton::clicked, this, &widget::onFatal);
}

widget::~widget()
{
    Logger::clean();
    delete ui;
}

void widget::onDebug()
{
    qDebug() << "Debug Log: qDebug()：用于输出调试信息";
}

void widget::onInfo()
{
    qInfo() << "Info Log: qInfo()：用于输出一般信息";
}

void widget::onWarning()
{
    qWarning() << "Warning Log: qWarning()：用于输出警告信息";
}

void widget::onCritical()
{
    qCritical() << "Critical Log: qCritical()：用于输出严重错误信息";
}

void widget::onFatal()
{
    qFatal("Fatal Log! qFatal()：用于输出致命错误信息，并且会终止程序");  // 注意，Fatal 是稍微有些不同的
}

