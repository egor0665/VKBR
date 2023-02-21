#include "predictionmodel.h"

PredictionModel::PredictionModel()
{

}

const QVector<ProjectSet> &PredictionModel::getProjects() const
{
    return projects;
}

void PredictionModel::setProjects(const QVector<ProjectSet> &newProjects)
{
    projects = newProjects;
}

int PredictionModel::addProject(ProjectSet project)
{
    QString type = project.getProjectType();
    bool foundType = false;
    int index = 0;
    if (type == "Связь")
    {
        int i=0;
        while ((i<projects.length()) && (projects[i].getProjectType() != "ДЗЗ") && (projects[i].getProjectType() != "ФКИ") && (projects[i].getProjectType() != "Другое"))
        {
            i++;
        }
        index = i;
    }
    else if (type == "ДЗЗ")
    {
        int i=0;
        while ((i<projects.length()) && (projects[i].getProjectType() != "ФКИ") && (projects[i].getProjectType() != "Другое"))
        {
            i++;
        }
        index = i;
    }
    else if (type == "ФКИ")
    {
        int i=0;
        while ((i<projects.length()) && (projects[i].getProjectType() != "Другое"))
        {
            i++;
        }
        index = i;
    }
    else if (type == "Другое")
    {
        index = projects.length() - 1;
    }

    projects.insert(index, project);
    return index;
    //projects.append(project);
}

bool PredictionModel::projectInModel(QString projectName)
{
    bool inModel = false;
    for(int i=0;i<projects.length();i++)
        if (projects[i].getProjectName() == projectName)
        {
            inModel= true;
            break;
        }
    return inModel;
}

void PredictionModel::removeProject(QString projectName)
{
    for(int i=0;i<projects.length();i++)
    {
        if (projects[i].getProjectName() == projectName)
        {
            projects.removeAt(i);
            break;
        }
    }
}

int PredictionModel::getProjectNumber(QString projectName)
{
    for(int i=0;i<projects.length();i++)
    {
        if (projects[i].getProjectName() == projectName)
            return i;
    }
}
