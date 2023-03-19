#ifndef TABCOMPARISONMODEL_H
#define TABCOMPARISONMODEL_H

#include <MainModel.h>
#include <qstring.h>



class TabComparisonModel
{
public:
    TabComparisonModel();
    TabComparisonModel(MainModel *_mainModel);
    QVector<QPair<QString,QStringList>> formCompareTable(QVector <QPair<QString,QString>> unitValues_1, QVector <QPair<QString,QString>> unitValues_2);
    qreal getNumberFromString(QString line, int param = 0);

private:
    MainModel *mainModel;
};

#endif // TABCOMPARISONMODEL_H
