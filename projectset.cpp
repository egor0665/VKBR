#include "projectset.h"

ProjectSet::ProjectSet()
{

}

ProjectSet::ProjectSet(const QString &projectType, const QString &projectName, int projectId, int unitId, const QVector<int> &EDWLaunchYears, const QVector<int> &seriesLaunchYears, const QVector<qreal> &spacecraftPrices, const QVector<QString> &boosterRockets, const QVector<int> &spacecraftBlocks, const QVector<qreal> &boosterRocketPrices, const QVector<qreal> &prePrices, int prePricesStartYear, const QVector<qreal> &firstUnitPrices, int firstUnitStartYear, const QVector<qreal> &lastUnitPrices, int lastUnitStartYear, const QVector<qreal> &postPrices, int postPricesStartYear, const QVector<qreal> &serialPrices, int serialPricesStartYear) : projectType(projectType),
    projectName(projectName),
    projectId(projectId),
    unitId(unitId),
    EDWLaunchYears(EDWLaunchYears),
    seriesLaunchYears(seriesLaunchYears),
    spacecraftPrices(spacecraftPrices),
    boosterRockets(boosterRockets),
    spacecraftBlocks(spacecraftBlocks),
    boosterRocketPrices(boosterRocketPrices),
    prePrices(prePrices),
    prePricesStartYear(prePricesStartYear),
    firstUnitPrices(firstUnitPrices),
    firstUnitStartYear(firstUnitStartYear),
    lastUnitPrices(lastUnitPrices),
    lastUnitStartYear(lastUnitStartYear),
    postPrices(postPrices),
    postPricesStartYear(postPricesStartYear),
    serialPrices(serialPrices),
    serialPricesStartYear(serialPricesStartYear)
{}

ProjectSet::ProjectSet(const QString &projectType, const QString &projectName, int projectId, int unitId, const QVector<qreal> &prePrices, int prePricesStartYear, const QVector<qreal> &firstUnitPrices, int firstUnitStartYear, const QVector<qreal> &lastUnitPrices, int lastUnitStartYear, const QVector<qreal> &postPrices, int postPricesStartYear, const QVector<qreal> &serialPrices, int serialPricesStartYear) : projectType(projectType),
    projectName(projectName),
    projectId(projectId),
    unitId(unitId),
    prePrices(prePrices),
    prePricesStartYear(prePricesStartYear),
    firstUnitPrices(firstUnitPrices),
    firstUnitStartYear(firstUnitStartYear),
    lastUnitPrices(lastUnitPrices),
    lastUnitStartYear(lastUnitStartYear),
    postPrices(postPrices),
    postPricesStartYear(postPricesStartYear),
    serialPrices(serialPrices),
    serialPricesStartYear(serialPricesStartYear)
{}

const QVector<int> &ProjectSet::getEDWLaunchYears() const
{
    return EDWLaunchYears;
}

void ProjectSet::setEDWLaunchYears(const QVector<int> &newEDWLaunchYears)
{
    EDWLaunchYears = newEDWLaunchYears;
}

const QVector<int> &ProjectSet::getSeriesLaunchYears() const
{
    return seriesLaunchYears;
}

void ProjectSet::setSeriesLaunchYears(const QVector<int> &newSeriesLaunchYears)
{
    seriesLaunchYears = newSeriesLaunchYears;
}

const QVector<qreal> &ProjectSet::getSpacecraftPrices() const
{
    return spacecraftPrices;
}

void ProjectSet::setSpacecraftPrices(const QVector<qreal> &newSpacecraftPrices)
{
    spacecraftPrices = newSpacecraftPrices;
}

const QVector<QString> &ProjectSet::getBoosterRockets() const
{
    return boosterRockets;
}

void ProjectSet::setBoosterRockets(const QVector<QString> &newBoosterRockets)
{
    boosterRockets = newBoosterRockets;
}

const QVector<int> &ProjectSet::getSpacecraftBlocks() const
{
    return spacecraftBlocks;
}

void ProjectSet::setSpacecraftBlocks(const QVector<int> &newSpacecraftBlocks)
{
    spacecraftBlocks = newSpacecraftBlocks;
}

const QVector<qreal> &ProjectSet::getBoosterRocketPrices() const
{
    return boosterRocketPrices;
}

void ProjectSet::setBoosterRocketPrices(const QVector<qreal> &newBoosterRocketPrices)
{
    boosterRocketPrices = newBoosterRocketPrices;
}

const QVector<qreal> &ProjectSet::getPrePrices() const
{
    return prePrices;
}

void ProjectSet::setPrePrices(const QVector<qreal> &newPrePrices)
{
    prePrices = newPrePrices;
}

int ProjectSet::getPrePricesStartYear() const
{
    return prePricesStartYear;
}

void ProjectSet::setPrePricesStartYear(int newPrePricesStartYear)
{
    prePricesStartYear = newPrePricesStartYear;
}

const QVector<qreal> &ProjectSet::getFirstUnitPrices() const
{
    return firstUnitPrices;
}

void ProjectSet::setFirstUnitPrices(const QVector<qreal> &newFirstUnitPrices)
{
    firstUnitPrices = newFirstUnitPrices;
}

int ProjectSet::getFirstUnitStartYear() const
{
    return firstUnitStartYear;
}

void ProjectSet::setFirstUnitStartYear(int newFirstUnitStartYear)
{
    firstUnitStartYear = newFirstUnitStartYear;
}

const QVector<qreal> &ProjectSet::getLastUnitPrices() const
{
    return lastUnitPrices;
}

void ProjectSet::setLastUnitPrices(const QVector<qreal> &newLastUnitPrices)
{
    lastUnitPrices = newLastUnitPrices;
}

int ProjectSet::getLastUnitStartYear() const
{
    return lastUnitStartYear;
}

void ProjectSet::setLastUnitStartYear(int newLastUnitStartYear)
{
    lastUnitStartYear = newLastUnitStartYear;
}

const QVector<qreal> &ProjectSet::getPostPrices() const
{
    return postPrices;
}

void ProjectSet::setPostPrices(const QVector<qreal> &newPostPrices)
{
    postPrices = newPostPrices;
}

int ProjectSet::getPostPricesStartYear() const
{
    return postPricesStartYear;
}

void ProjectSet::setPostPricesStartYear(int newPostPricesStartYear)
{
    postPricesStartYear = newPostPricesStartYear;
}

const QVector<qreal> &ProjectSet::getSerialPrices() const
{
    return serialPrices;
}

void ProjectSet::setSerialPrices(const QVector<qreal> &newSerialPrices)
{
    serialPrices = newSerialPrices;
}

int ProjectSet::getSerialPricesStartYear() const
{
    return serialPricesStartYear;
}

void ProjectSet::setSerialPricesStartYear(int newSerialPricesStartYear)
{
    serialPricesStartYear = newSerialPricesStartYear;
}

const QString &ProjectSet::getProjectType() const
{
    return projectType;
}

void ProjectSet::setProjectType(const QString &newProjectType)
{
    projectType = newProjectType;
}

const QString &ProjectSet::getProjectName() const
{
    return projectName;
}

void ProjectSet::setProjectName(const QString &newProjectName)
{
    projectName = newProjectName;
}

int ProjectSet::getProjectId() const
{
    return projectId;
}

void ProjectSet::setProjectId(int newProjectId)
{
    projectId = newProjectId;
}

int ProjectSet::getUnitId() const
{
    return unitId;
}

void ProjectSet::setUnitId(int newUnitId)
{
    unitId = newUnitId;
}
