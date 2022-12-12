#ifndef ORGANIZATION_H
#define ORGANIZATION_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Organization
{
public:
    Organization();
    Organization(int id, const QString &name);
    int id() const;
    void setId(int newId);
    const QString &name() const;
    void setName(const QString &newName);

private:
    int _id;
    QString _name ;
};

#endif // ORGANIZATION_H
