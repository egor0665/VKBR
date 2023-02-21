#ifndef DBORGANIZATION_H
#define DBORGANIZATION_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class DBOrganization
{
public:
    DBOrganization();
    DBOrganization(int id, const QString &name);
    int id() const;
    void setId(int newId);
    const QString &name() const;
    void setName(const QString &newName);

private:
    int _id;
    QString _name ;
};

#endif // DBORGANIZATION_H
