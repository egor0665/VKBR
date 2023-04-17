#include "tabeditusermodel.h"

#include <DBUser.h>

TabEditUserModel::TabEditUserModel()
{

}

//TabEditUserModel::TabEditUserModel(MainModel *_mainModel)
//{
//    mainModel = _mainModel;
//}

TabEditUserModel::TabEditUserModel(DataBase *db)
{
    this->db = db;
}

int TabEditUserModel::getUserIdByName(QString name)
{
    return db->getUserIdByName(name);
}

DBUser TabEditUserModel::getUserById(int userId)
{
    return db->getUserById(userId);
}

void TabEditUserModel::addUserToDB(QString name, QString role, QString password)
{
    db->addUserToDB(DBUser(-1, name, role, password));
}

void TabEditUserModel::updateUserDB(int id, QString name, QString role, QString password)
{
    db->updateUserDB(DBUser(id, name, role, password));
}

void TabEditUserModel::deleteUserFromDB(int userId)
{
    db->deleteUserFromDB(userId);
}

bool TabEditUserModel::lastAdmin()
{
    if (db->getAdminUserCount()>1)
        return false;
    else
        return true;
}
