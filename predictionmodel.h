#ifndef PREDICTIONMODEL_H
#define PREDICTIONMODEL_H

#include <ProjectSet.h>
#include <QObject>
#include <QWidget>

class PredictionModel
{
public:
    PredictionModel();

    const QVector<ProjectSet> &getProjects() const;
    void setProjects(const QVector<ProjectSet> &newProjects);


    void removeProject(QString projectName);

    bool projectInModel(QString projectName);

    int getProjectNumber(QString projectName);

    int addProject(ProjectSet project);
    QString getProjectType(QString projectName);
    ProjectSet getProjectSetByName(QString projectName);
    int getUnitLifetime(QString projectName);
    const QVector<qreal> &getInflationPercents() const;
    void setInflationPercents(const QVector<qreal> &newInflationPercents);
    int getProjectIdByName(QString projectName);

protected:
    QVector <ProjectSet> projects;
    QVector <qreal> inflationPercents;
};

#endif // PREDICTIONMODEL_H
