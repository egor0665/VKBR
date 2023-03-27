#include "fileprojectvalue.h"

#include <qvector.h>

FileProjectValue::FileProjectValue()
{


}

const QString &FileProjectValue::getProjectName() const
{
    return projectName;
}

void FileProjectValue::setProjectName(const QString &newProjectName)
{
    projectName = newProjectName;
}

int FileProjectValue::getProjectId() const
{
    return projectId;
}

void FileProjectValue::setProjectId(int newProjectId)
{
    projectId = newProjectId;
}

const QVector<int> &FileProjectValue::getOkrYears() const
{
    return okrYears;
}

void FileProjectValue::setOkrYears(const QVector<int> &newOkrYears)
{
    okrYears = newOkrYears;
}

const QVector<int> &FileProjectValue::getSerialYears() const
{
    return serialYears;
}

void FileProjectValue::setSerialYears(const QVector<int> &newSerialYears)
{
    serialYears = newSerialYears;
}

const QVector<int> &FileProjectValue::getUnitBlocks() const
{
    return unitBlocks;
}

void FileProjectValue::setUnitBlocks(const QVector<int> &newUnitBlocks)
{
    unitBlocks = newUnitBlocks;
}

const QVector<QString> &FileProjectValue::getLaunchValues() const
{
    return launchValues;
}

void FileProjectValue::setLaunchValues(const QVector<QString> &newLaunchValues)
{
    launchValues = newLaunchValues;
}

const QVector<int> &FileProjectValue::getLaunchIds() const
{
    return launchIds;
}

void FileProjectValue::setLaunchIds(const QVector<int> &newLaunchIds)
{
    launchIds = newLaunchIds;
}

FileProjectValue::FileProjectValue(const QString &projectName, int projectId, const QVector<int> &okrYears, const QVector<int> &serialYears, const QVector<int> &unitBlocks, const QVector<QString> &launchValues, const QVector<int> &launchIds) : projectName(projectName),
    projectId(projectId),
    okrYears(okrYears),
    serialYears(serialYears),
    unitBlocks(unitBlocks),
    launchValues(launchValues),
    launchIds(launchIds)
{}

FileProjectValue::FileProjectValue(const QString &projectName, const QVector<int> &okrYears, const QVector<int> &serialYears, const QVector<int> &unitBlocks, const QVector<QString> &launchValues) : projectName(projectName),
    okrYears(okrYears),
    serialYears(serialYears),
    unitBlocks(unitBlocks),
    launchValues(launchValues)
{}

FileProjectValue::FileProjectValue(int projectId, const QVector<int> &okrYears, const QVector<int> &serialYears, const QVector<int> &unitBlocks, const QVector<int> &launchIds) : projectId(projectId),
    okrYears(okrYears),
    serialYears(serialYears),
    unitBlocks(unitBlocks),
    launchIds(launchIds)
{}
