#ifndef TEST_TESTS_H
#define TEST_TESTS_H

#include <DataBase.h>
#include <QObject>

class Test_Tests : public QObject
{
    Q_OBJECT
public:
    explicit Test_Tests(QObject *parent = 0);

private slots: // должны быть приватными
    void DBCreateGetCheck(); // int max(int, int)
    void DBDeleteCheck();
private:
    DataBase db;
};

#endif // TEST_TESTS_H
