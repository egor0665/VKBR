#include "DBunit.h"

DBUnit::DBUnit()
{

}

int DBUnit::id() const
{
    return _id;
}

void DBUnit::setId(int newId)
{
    _id = newId;
}

const QString &DBUnit::name() const
{
    return _name;
}

void DBUnit::setName(const QString &newName)
{
    _name = newName;
}

bool DBUnit::project() const
{
    return _project;
}

void DBUnit::setProject(bool newProject)
{
    _project = newProject;
}

const QString &DBUnit::objective() const
{
    return _objective;
}

void DBUnit::setObjective(const QString &newObjective)
{
    _objective = newObjective;
}

const QString &DBUnit::work_status() const
{
    return _work_status;
}

void DBUnit::setWork_status(const QString &newWork_status)
{
    _work_status = newWork_status;
}

int DBUnit::developer_id() const
{
    return _developer_id;
}

void DBUnit::setDeveloper_id(int newDeveloper_id)
{
    _developer_id = newDeveloper_id;
}

int DBUnit::manufacturer_id() const
{
    return _manufacturer_id;
}

void DBUnit::setManufacturer_id(int newManufacturer_id)
{
    _manufacturer_id = newManufacturer_id;
}

int DBUnit::launches() const
{
    return _launches;
}

void DBUnit::setLaunches(int newLaunches)
{
    _launches = newLaunches;
}

int DBUnit::customer_id() const
{
    return _customer_id;
}

void DBUnit::setCustomer_id(int newCustomer_id)
{
    _customer_id = newCustomer_id;
}

int DBUnit::successful() const
{
    return _successful;
}

void DBUnit::setSuccessful(int newSuccessful)
{
    _successful = newSuccessful;
}

const QDateTime &DBUnit::first_launch() const
{
    return _first_launch;
}

void DBUnit::setFirst_launch(const QDateTime &newFirst_launch)
{
    _first_launch = newFirst_launch;
}

int DBUnit::first_launch_spaceport_id() const
{
    return _first_launch_spaceport_id;
}

void DBUnit::setFirst_launch_spaceport_id(int newFirst_launch_spaceport_id)
{
    _first_launch_spaceport_id = newFirst_launch_spaceport_id;
}

const QString &DBUnit::financing_type() const
{
    return _financing_type;
}

void DBUnit::setFinancing_type(const QString &newFinancing_type)
{
    _financing_type = newFinancing_type;
}

const QString &DBUnit::control_system_type() const
{
    return _control_system_type;
}

void DBUnit::setControl_system_type(const QString &newControl_system_type)
{
    _control_system_type = newControl_system_type;
}

qreal DBUnit::price() const
{
    return _price;
}

void DBUnit::setPrice(qreal newPrice)
{
    _price = newPrice;
}

int DBUnit::price_year() const
{
    return _price_year;
}

void DBUnit::setPrice_year(int newPrice_year)
{
    _price_year = newPrice_year;
}

const QString &DBUnit::purpose() const
{
    return _purpose;
}

void DBUnit::setPurpose(const QString &newPurpose)
{
    _purpose = newPurpose;
}

const QString &DBUnit::unit_class() const
{
    return _unit_class;
}

void DBUnit::setUnit_class(const QString &newUnit_class)
{
    _unit_class = newUnit_class;
}

QStringList DBUnit::getValues()
{
    QStringList values;

    values.append(this->unit_class());
    values.append(this->name());
    values.append(this->purpose());
    values.append(QString::number(this->project()));
    values.append(this->objective());
    values.append(this->work_status());
    values.append(QString::number(this->developer_id()));
    values.append(QString::number(this->extra_developer_id()));
    values.append(QString::number(this->manufacturer_id()));
    values.append(QString::number(this->launches()));
    values.append(QString::number(this->successful()));
    values.append(QString::number(this->customer_id()));
    values.append(this->first_launch().toString());
    values.append(QString::number(this->first_launch_spaceport_id()));
    values.append(this->financing_type());
    values.append(this->control_system_type());
    values.append(QString::number(this->price()));
    values.append(QString::number(this->price_year()));

    return values;
}

int DBUnit::extra_developer_id() const
{
    return _extra_developer_id;
}

void DBUnit::setExtra_developer_id(int newExtra_developer_id)
{
    _extra_developer_id = newExtra_developer_id;
}

const QString &DBUnit::image_url() const
{
    return _image_url;
}

void DBUnit::setImage_url(const QString &newImage_url)
{
    _image_url = newImage_url;
}

DBUnit::DBUnit(int id, const QString &unit_class, const QString &name, const QString &purpose, bool project, const QString &objective, const QString &work_status, int developer_id, int extra_developer_id, int manufacturer_id, int launches, int customer_id, int successful, const QDateTime &first_launch, int first_launch_spaceport_id, const QString &financing_type, const QString &control_system_type, const QString &image_url, qreal price, int price_year) : _id(id),
    _unit_class(unit_class),
    _name(name),
    _purpose(purpose),
    _project(project),
    _objective(objective),
    _work_status(work_status),
    _developer_id(developer_id),
    _extra_developer_id(extra_developer_id),
    _manufacturer_id(manufacturer_id),
    _launches(launches),
    _customer_id(customer_id),
    _successful(successful),
    _first_launch(first_launch),
    _first_launch_spaceport_id(first_launch_spaceport_id),
    _financing_type(financing_type),
    _control_system_type(control_system_type),
    _image_url(image_url),
    _price(std::move(price)),
    _price_year(price_year)
{}
