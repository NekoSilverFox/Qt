#ifndef LOGGER_H
#define LOGGER_H

#include <QFile>
#include <QDebug>
#include <QHash>

/**
 * @brief 基于单例模式的 Logger 类
 */
class Logger
{
public:
    static void init(const QString &path, const QString &date, const QString &sep);
    static void msgOutput(QtMsgType type, const QMessageLogContext& context, const QString& msg);
    static void clean();

private:
    static QFile* _logFile; // 日志文件指针
    static bool _isInit;    // 是否初始化
    static QHash<QtMsgType, QString> _contextName;  // 日志级别和对应字符串
    static QString _date;   // 日志中日期格式
    static QString _sep;    // 日志中分隔符
};

#endif // LOGGER_H
