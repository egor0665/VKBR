#ifndef FILEPROJECTVALUE_H
#define FILEPROJECTVALUE_H

#include <qstring.h>
#include <qvector.h>



class FileProjectValue
{
public:
    FileProjectValue();
    FileProjectValue(const QString &projectName, const QVector<int> &okrYears, const QVector<int> &serialYears, const QVector<int> &unitBlocks, const QVector<QString> &launchValues);
    FileProjectValue(int projectId, const QVector<int> &okrYears, const QVector<int> &serialYears, const QVector<int> &unitBlocks, const QVector<int> &launchIds);
    FileProjectValue(const QString &projectName, int projectId, const QVector<int> &okrYears, const QVector<int> &serialYears, const QVector<int> &unitBlocks, const QVector<QString> &launchValues, const QVector<int> &launchIds);
    const QString &getProjectName() const;
    void setProjectName(const QString &newProjectName);
    int getProjectId() const;
    void setProjectId(int newProjectId);
    const QVector<int> &getOkrYears() const;
    void setOkrYears(const QVector<int> &newOkrYears);
    const QVector<int> &getSerialYears() const;
    void setSerialYears(const QVector<int> &newSerialYears);
    const QVector<int> &getUnitBlocks() const;
    void setUnitBlocks(const QVector<int> &newUnitBlocks);
    const QVector<QString> &getLaunchValues() const;
    void setLaunchValues(const QVector<QString> &newLaunchValues);
    const QVector<int> &getLaunchIds() const;
    void setLaunchIds(const QVector<int> &newLaunchIds);

private:
    QString projectName;
    int projectId;

    QVector<int> okrYears;
    QVector<int> serialYears;

    QVector<int> unitBlocks;

    QVector<QString> launchValues;
    QVector<int> launchIds;
};

#endif // FILEPROJECTVALUE_H
