#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QVector>
#include <mainmodel.h>
#include "database.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    database db;
    MainModel model;

    QTreeWidgetItem *addTreeRoot(QString name);
protected:
    void startUI();
    void tab2Init();
    void rebuildCompareTable(QString unitName1, QString unitName2);
    void addTreeChild2(QTreeWidgetItem *parent, QString name);
    void addTreeChild(QTreeWidgetItem *parent, QString name, QVector <QString> child_array);
    QString classSelect(QString _class);
private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
