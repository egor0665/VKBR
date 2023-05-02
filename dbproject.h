#ifndef DBPROJECT_H
#define DBPROJECT_H

#include <qstring.h>



class DBProject
{
public:
    DBProject();
    DBProject(int id, const QString &name, const QString &type, int unit_id, const QString &first_unit_prices, const QString &last_unit_prices, const QString &pre_prices, const QString &post_prices, const QString &serial_prices);

    int id() const;
    const QString &name() const;
    const QString &type() const;
    int unit_id() const;

    const QString &pre_prices() const;
    const QString &post_prices() const;

    const QString &serial_prices() const;

    const QString &first_unit_prices() const;
    const QString &last_unit_prices() const;

    void setId(int newId);
    void setName(const QString &newName);
    void setType(const QString &newType);
    void setUnit_id(int newUnit_id);
    void setFirst_unit_prices(const QString &newFirst_unit_prices);
    void setLast_unit_prices(const QString &newLast_unit_prices);
    void setPre_prices(const QString &newPre_prices);
    void setPost_prices(const QString &newPost_prices);
    void setSerial_prices(const QString &newSerial_prices);

private:
    int _id;
    QString _name;
    QString _type;
    int _unit_id;
    QString _first_unit_prices;
    QString _last_unit_prices;
    QString _pre_prices;
    QString _post_prices;
    QString _serial_prices;
//    QVector <qreal> _unit_prices();
//    QVector <qreal> _pre_prices();
//    QVector <qreal> _post_prices();
};

#endif // DBPROJECT_H
