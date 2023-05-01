#include "mainwindow.h"
#include <QtTest/QTest>
#include <QApplication>
#include <Test_Tests.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTest::qExec(new Test_Tests, argc, argv);
    MainWindow w;

    w.show();
    return a.exec();
}
