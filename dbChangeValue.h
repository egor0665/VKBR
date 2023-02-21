#ifndef DBCHANGEVALUE_H
#define DBCHANGEVALUE_H

#include <QString>

class dbChangeValue
{
    QString id;
    QString header;
    QString value;
public:
    dbChangeValue(const QString &id, const QString &header, const QString &value);
    dbChangeValue() {}


    const QString &getId() const;
    const QString &getHeader() const;
    const QString &getValue() const;
    void setValue(const QString &newValue);
};

inline const QString &dbChangeValue::getId() const
{
    return id;
}

inline const QString &dbChangeValue::getHeader() const
{
    return header;
}

inline const QString &dbChangeValue::getValue() const
{
    return value;
}

inline void dbChangeValue::setValue(const QString &newValue)
{
    value = newValue;
}

inline dbChangeValue::dbChangeValue(const QString &id, const QString &header, const QString &value) : id(id),
    header(header),
    value(value)
{}
#endif // DBCHANGEVALUE_H
