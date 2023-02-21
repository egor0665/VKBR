#ifndef DBUNIT_H
#define DBUNIT_H

#include <QDateTime>
#include <QString>



class DBUnit
{
public:

    const int UNIT_ROW_NUM = 15;
    const QStringList UNIT_VALUES = {"Класс",
                                     "Название",
                                     "Назначение",
                                     "Проектный",
                                     "Цель",
                                     "Состояние работ",
                                     "Разработчик",
                                     "Разработчик 2",
                                     "Производитель",
                                     "Запусков",
                                     "Заказчик",
                                     "Успешных запусков",
                                     "Первый запуск",
                                     "Космодром первого запуска",
                                     "Тип финансирования",
                                     "Система контроля"};
    DBUnit();
    DBUnit(int id,
         const QString &unit_class,
         const QString &name,
         const QString &purpose,
         bool project,
         const QString &objective,
         const QString &work_status,
         int developer_id,
         int extra_developer_id,
         int manufacturer_id,
         int launches,
         int customer_id,
         int successful,
         const QDateTime &first_launch,
         int first_launch_spaceport_id,
         const QString &financing_type,
         const QString &control_system_type,
         const QString &image_url,
         qreal price,
         int price_year);

    int id() const;

    void setId(int newId);

    const QString &unit_class() const;
    void setUnit_class(const QString &newUnit_class);

    const QString &name() const;
    void setName(const QString &newName);

    bool project() const;
    void setProject(bool newProject);

    const QString &objective() const;
    void setObjective(const QString &newObjective);

    const QString &work_status() const;
    void setWork_status(const QString &newWork_status);

    int developer_id() const;
    void setDeveloper_id(int newDeveloper_id);

    int manufacturer_id() const;
    void setManufacturer_id(int newManufacturer_id);

    int launches() const;
    void setLaunches(int newLaunches);

    int customer_id() const;
    void setCustomer_id(int newCustomer_id);

    int successful() const;
    void setSuccessful(int newSuccessful);

    const QDateTime &first_launch() const;
    void setFirst_launch(const QDateTime &newFirst_launch);

    int first_launch_spaceport_id() const;
    void setFirst_launch_spaceport_id(int newFirst_launch_spaceport_id);

    const QString &financing_type() const;
    void setFinancing_type(const QString &newFinancing_type);

    const QString &control_system_type() const;
    void setControl_system_type(const QString &newControl_system_type);

    const QString &image_url() const;
    void setImage_url(const QString &newImage_url);

    qreal price() const;
    void setPrice(qreal newPrice);

    int price_year() const;
    void setPrice_year(int newPrice_year);

    const QString &purpose() const;
    void setPurpose(const QString &newPurpose);

    QStringList getValues();


    int extra_developer_id() const;
    void setExtra_developer_id(int newExtra_developer_id);

private:
    int _id;
    QString _unit_class ;
    QString _name;
    QString _purpose;
    bool _project;
    QString _objective;
    QString _work_status;
    int _developer_id;
    int _extra_developer_id;
    int _manufacturer_id;
    int _launches;
    int _customer_id;
    int _successful;
    QDateTime _first_launch;
    int _first_launch_spaceport_id;
    QString _financing_type;
    QString _control_system_type;
    QString _image_url;
    qreal _price;
    int _price_year;
};

#endif // DBUNIT_H
