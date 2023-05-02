#ifndef TEST_TESTS_H
#define TEST_TESTS_H

#include <DataBase.h>
#include <QObject>

class Test_Tests : public QObject
{
    Q_OBJECT
public:
    explicit Test_Tests(QObject *parent = 0);

private slots:
    void DBCreateGetCheck();
    void tabCatalogAndComparisonCheck();
    void tabEditUserModelCheck();
    void tabEditCraftModelCheck();
    void tabEditExtrasModelCheck();
    void tabEditProjectModelCheck();
    void tabPredictionModelCheck();
    void fileSaveTest();
    void DBDeleteCheck();
private:
    DataBase db;
};

#endif // TEST_TESTS_H
