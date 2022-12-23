#ifndef TESTQSTRING_H
#define TESTQSTRING_H

#include <QtTest/QtTest>
#include <QObject>

class TestQString : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();

    void to_upper();

    void cleanupTestCase();
};

#endif // TESTQSTRING_H
