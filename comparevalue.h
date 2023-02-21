#ifndef COMPAREVALUE_H
#define COMPAREVALUE_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class CompareValue
{
public:
    CompareValue(const QString &parameter, const QVector<qreal> &values);

    CompareValue(){};
    CompareValue(QString &parameter, QVector <qreal> values) : _parameter(parameter),
        _values(values)
    {}
    QString _parameter;
    QVector <qreal> _values;
};

#endif // COMPAREVALUE_H
