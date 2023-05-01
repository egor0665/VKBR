#include "tests.h"

Tests::Tests(QObject *parent, const QStringList& list) :
    QObject(parent)
{
}

int Tests::max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

int Tests::min(int a, int b)
{
    if(a < b)
        return a;
    return b;
}
