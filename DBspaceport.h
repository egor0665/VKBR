#ifndef DBSPACEPORT_H
#define DBSPACEPORT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class DBSpaceport
{
public:
    DBSpaceport();
    DBSpaceport(int id, const QString &name);
    int id() const;
    void setId(int newId);
    const QString &name() const;
    void setName(const QString &newName);

private:
    int _id;
    QString _name ;
};

#endif // DBSPACEPORT_H
