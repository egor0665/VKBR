#include "tabeditusermodel.h"

#include <DBUser.h>

TabEditUserModel::TabEditUserModel()
{

}

TabEditUserModel::TabEditUserModel(MainModel *_mainModel)
{
    mainModel = _mainModel;
}

int TabEditUserModel::getUserIdByName(QString name)
{
    return mainModel->db.getUserIdByName(name);
}

DBUser TabEditUserModel::getUserById(int userId)
{
    return mainModel->db.getUserById(userId);
}

void TabEditUserModel::addUserToDB(QString name, QString role, QString password)
{
    mainModel->db.addUserToDB(DBUser(-1, name, role, password));
}

void TabEditUserModel::updateUserDB(int id, QString name, QString role, QString password)
{
    mainModel->db.updateUserDB(DBUser(id, name, role, password));
}

void TabEditUserModel::deleteUserFromDB(int userId)
{
    mainModel->db.deleteUserFromDB(userId);
}
