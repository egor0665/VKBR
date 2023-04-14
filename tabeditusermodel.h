#ifndef TABEDITUSERMODEL_H
#define TABEDITUSERMODEL_H

#include <MainModel.h>



class TabEditUserModel
{
public:
    TabEditUserModel();
//    TabEditUserModel(MainModel* _mainModel);

    int getUserIdByName(QString name);
    DBUser getUserById(int userId);
    void addUserToDB(QString name, QString role, QString password);
    void updateUserDB(int id, QString name, QString role, QString password);
    void deleteUserFromDB(int userId);
    bool lastAdmin();
    TabEditUserModel(database *db);
private:
    database* db;
};

#endif // TABEDITUSERMODEL_H
