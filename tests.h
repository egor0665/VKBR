#ifndef TESTS_H
#define TESTS_H

#include <QObject>
#include <QWidget>

class Tests : public QObject
{
    Q_OBJECT
public:
    explicit Tests(QObject *parent, const QStringList& list);

public slots:
    int max(int a, int b);
    int min(int a, int b);

};

#endif // TESTS_H
