<p align="center">
 <img width="100px" src="https://raw.githubusercontent.com/NekoSilverFox/NekoSilverfox/403ab045b7d9adeaaf8186c451af7243f5d8f46d/icons/silverfox.svg" align="center" alt="NekoSilverfox" />
 <h1 align="center">Qt</h1>
 <p align="center"><b>-------</b></p>
</p>


<div align=center>


[![License](https://img.shields.io/badge/license-Apache%202.0-brightgreen)](LICENSE)



<div align=left>
<!-- 顶部至此截止 -->


# 简介

- widget.hpp

```c++
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget  // Widget 继承 QWidget
{
    Q_OBJECT  // Q_OBJECT 宏，写了这个宏就支持了 Qt 中的信号和槽机制

public:
    Widget(QWidget *parent = nullptr); // 构造函数
    ~Widget();
};
#endif // WIDGET_H

```





- main.cpp

```c++
#include "widget.h"

#include <QApplication>  // 包含头文件 - 应用程序

/** 程序入口
 * @brief main
 * @param argc 命令行变量数量
 * @param argv 命令行变量数组
 * @return
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // 应用程序对象 a，在 Qt 中有且仅有一个
    Widget w;  // 窗口对象
    w.show();  // 弹出窗口（窗口默认不会弹出）

    return a.exec(); // a.exec() 进入消息循环机制，避免程序一闪而过，类似死循环
}

```



## .pro 介绍

```makefile
QT       += core gui  # Qt 中包含的模块

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets  # 大于 4 版本；包含 widget 模块（Qt5 之前的版本 widget 是包含在 GUI 的）

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 源文件
SOURCES += \
    main.cpp \
    widget.cpp

HEADERS += \
    widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

```



## 命名规范和快捷键

- 类名首字母大写，驼峰式命名（首字母大写）
- 函数、变量首字母小写，连接首字母大写



**快捷键：**

- Ctrl + R 运行
- Ctrl + B 编译
- Ctrl + F 查找
- F1 帮助文档
- Ctrl + 滚轮  字体缩放
- Crrl + I 自动对齐
- Ctrl + Shift + 上下 整行移动
- F4 同名之间的 .h .cpp 切换



**Qt 中所有的窗口叫 Widget**



# 控件

## Weight 窗口

| 函数名                      | 描述                                           |
| --------------------------- | ---------------------------------------------- |
| setWindowTitle(QStrging)    | 设置窗口标题                                   |
| setFixedSize(hight, weight) | 设置固定的窗口大小（设置之后窗口不能人为缩放） |
| show()                      | 显示此窗口                                     |
|                             |                                                |



**信号和槽**

| 槽    | 描述     |
| ----- | -------- |
| close | 关闭窗口 |
|       |          |
|       |          |



## QPushButton

| 函数名                | 描述           |
| --------------------- | -------------- |
| setParent(obj)        | 设置按钮的父类 |
| move(x, y)            | 移动按钮       |
| resize(hight, weight) | 设置按钮大小   |
| setText(QString)      | 设置按钮文本   |



| 信号    | 描述 |
| ------- | ---- |
| clicked | 点击 |
|         |      |
|         |      |



# 信号和槽

## 总结

- 一个信号可以连接多个槽
- 多个信号是可以连接同一个槽
- 信号可以连接信号
- **信号和槽的参数类型必须一一对应**，但**信号参数的个数可以多于槽的个数**（反之不可）
- 信号与槽直连的连接可以断开（`disconnect(发送方, 信号, 接收方, 槽)`）



# lambda 表达式

C++11中的Lambda表达式**用于定义并创建匿名的函数对象**，以简化编程工作。首先看一下Lambda表达式的基本构成：

`[函数对象参数](操作符重载函数参数) mutable -> 返回值 {函数体}`

```c++
[capture](parameters) mutable ->return-type
{
	statement
}
```



**`[]` 里的函数对象参数有以下几种：**

- `空` - 没有使用任何函数对象参数
- `=` - 函数体内可以使用**Lambda所在作用范围内所有可见的局部变量（包括Lambda所在类的this）**，并且是**==值传递方式==**（相当于编译器自动为我们按值传递了所有局部变量）==最常用==
- `&` - 函数体内可以使用**Lambda所在作用范围内所有可见的局部变量（包括Lambda所在类的this）**，并且是**==引用传递方式==**（相当于编译器自动为我们按引用传递了所有局部变量）
- `this` - 函数体内可以使用Lambda所在类中的成员变量
- `变量名` - 将变量名按值进行传递。按值进行传递时，**函数体内不能修改传递进来的变量的拷贝**，因为默认情况下函数是const的。**要修改传递进来的变量的拷贝**，可以添加 `mutable` 修饰符
- `&a` - 将a按引用进行传递
- `a, &b` - 将a按值进行传递，b按引用进行传递
- `=, &a, &b` - 除a和b按引用进行传递外，其他参数都按值进行传递
- `&, a, b` - 除a和b按值进行传递外，其他参数都按引用进行传递



**操作符重载函数参数：**

标识重载的()操作符的参数，没有参数时，这部分可以省略。参数可以通过按值（如：(a,b)）和按引用（如：(&a,&b)）两种方式进行传递。



**可修改标示符：**

`mutable` 声明，这部分可以省略。按值传递函数对象参数时，加上 `mutable` 修饰符后，可以修改按值传递进来的拷贝（注意是能修改拷贝，而不是值本身）。



**函数返回值：**

`-> 返回值类型`，标识函数返回值的类型，当返回值为 void，或者函数体中只有一处 return 的地方（此时编译器可以自动推断出返回值类型）时，这部分可以省略。



**函数体：**

{}，标识函数的实现，这部分不能省略，但函数体可以为空。































