#ifndef BOOSTER_ROCKET_H
#define BOOSTER_ROCKET_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class Booster_rocket
{
public:
    const int BOOSTER_ROCKET_DEF_ROW_NUM = 5;
    const QStringList BOOSTER_ROCKET_VALUES = {"Класс грузоподъемности", "Кол-во ступеней", "Вид топлива", "phys_info", "econ_info"};

    Booster_rocket();
    Booster_rocket(int id, const QString &load_class, int stages_num, const QString &fuel_type, const QString &phys_info);
    int id() const;
    void setId(int newId);
    const QString &load_class() const;
    void setLoad_class(const QString &newLoad_class);
    int stages_num() const;
    void setStages_num(int newStages_num);
    bool upper_block() const;
    void setUpper_block(bool newUpper_block);
    bool induction_block() const;
    void setInduction_block(bool newInduction_block);
    bool aggregate_module() const;
    void setAggregate_module(bool newAggregate_module);
    const QString &fairing_type() const;
    void setFairing_type(const QString &newFairing_type);
    const QString &fuel_type() const;
    void setFuel_type(const QString &newFuel_type);
    const QString &phys_info() const;
    void setPhys_info(const QString &newPhys_info);

    QStringList getValues();

    const QString &econ_info() const;
    void setEcon_info(const QString &newEcon_info);

private:
    int _id;
    QString _load_class;
    int _stages_num;
    QString _fuel_type;
    QString _phys_info;
    QString _econ_info;

};

#endif // BOOSTER_ROCKET_H
