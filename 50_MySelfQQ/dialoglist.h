#ifndef DIALOGLIST_H
#define DIALOGLIST_H

#include <QWidget>
#include <QToolButton>


namespace Ui {
class DialogList;
}

class DialogList : public QWidget
{
    Q_OBJECT

public:
    explicit DialogList(QWidget *parent = nullptr);
    ~DialogList();

private:
    Ui::DialogList *ui;

    QVector<QToolButton*> vToolBtn; // 用容器保存住按钮，方便后续操作
    QVector<bool> vIsOpen;  // 对应人员的窗口是否已经被打开
};

#endif // DIALOGLIST_H
