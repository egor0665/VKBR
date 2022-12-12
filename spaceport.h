#ifndef SPACEPORT_H
#define SPACEPORT_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Spaceport
{
public:
    Spaceport();
    Spaceport(int id, const QString &name);
    int id() const;
    void setId(int newId);
    const QString &name() const;
    void setName(const QString &newName);

private:
    int _id;
    QString _name ;
};

#endif // SPACEPORT_H
