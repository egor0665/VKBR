#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QVector>
#include <SaveToPdfDialog.h>
#include <TabCatalogAndComparisonModel.h>
#include <TabCatalogModel.h>
#include <TabComparisonModel.h>
#include <TabEditDBModel.h>
#include <TabEditUserModel.h>
#include <TabNewCraftModel.h>
#include <TabNewExtrasModel.h>
#include <TabNewProjectModel.h>
#include <UnitComparator.h>
#include <dbChangeValue.h>
#include <mainmodel.h>
#include <predictionModel.h>
#include <tabPredictionModel.h>
#include <userLoginWindow.h>
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

    TabPredictionModel tabPredictionModel;
    TabNewProjectModel tabNewProjectModel;
    TabEditDBModel tabEditDBModel;
    TabNewExtrasModel tabNewExtrasModel;
    TabNewCraftModel tabNewCraftModel;
    TabCatalogAndComparisonModel tabCatalogAndComparisonModel;
    TabEditUserModel tabEditUserModel;


    UnitComparator comparator;
    bool predictionTableEditedByUser;
    bool listWidgetEditedByUser;

    userLoginWindow loginWindow;
    SaveToPdfDialog saveToPdfDialog;

    QString saveFilePath;
    bool predictionTableChanged;

    QTreeWidgetItem *addTreeRoot(QString name);
    void addUnitTabUpdateValues();
    void saveToFile(QString filePath);
    void buildEditUsersTab();
    void enableTabsLogin();
    void showHintMessage(QString text, QString type);
public slots:
    void login(QString name,QString password);
    void closeApp();
    void saveToPdf(QString name, QVector<QString> values, QVector<QPair<QVector<QString>,QString>> chartValues, int startYear, int endYear);
    void enableUI();
protected:
    QDoubleSpinBox *maxPayloadField;
    QDoubleSpinBox *minPayloadField;
    QDoubleSpinBox *weightField;
    QDoubleSpinBox *activeLifetimeField;
    QTextEdit *physInfoField;
    QTextEdit *econInfoField;
    QComboBox *projectTypeComboBox;
    QLineEdit *projectNameField;
    //QVector<QString> comparisonTableFields;

    void buildDisplayTab();
    void buildCompareTab();
    void buildAddUnitTab();
    void rebuildCompareTable(QVector<QString> selectedUnits);
    void addTreeChild2(QTreeWidgetItem *parent, QString name);
    void addTreeChild(QTreeWidgetItem *parent, QString name, QVector <QString> child_array);
    QString classSelect(QString _class);
    void buildChart();
    void buildChartTable();
    void buildEditDBTab();
    bool readyToStore;
    QVector<dbChangeValue> dbValuesToChange;

    void rebuildTabs();
    void buildEditProjectTab();
    void buildAddExtrasTab();
    void buildPredictionTab();
    void setTableWidgetRowColor(QTableWidget *tableWidget, int row, int startColumn, QColor color);
    void rebuildEditLaunchTable(QString boosterRocket, QString upperBlock, QString spaceport);
    void startAuth();
private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_tableWidget_4_cellDoubleClicked(int row, int column);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_comboBoxUnitClass_currentIndexChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_comboBox_5_currentIndexChanged(const QString &arg1);

    void on_pushButton_11_clicked();

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_comboBox_6_currentIndexChanged(const QString &arg1);

    void on_comboBox_7_currentIndexChanged(const QString &arg1);

    void on_comboBox_8_currentIndexChanged(const QString &arg1);

    void on_tableWidget_8_comboBox_index_changed(const QString &arg1);

    void on_tableWidget_8_cellChanged(int row, int column, QString spaceCraft = "");

    void on_pushButton_12_clicked();

    void on_comboBox_10_currentIndexChanged(const QString &arg1);

    void on_pushButton_15_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_16_clicked();

    void on_listWidget_2_itemChanged(QListWidgetItem *item);

    void on_pushButton_18_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_9_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_comboBox_4_currentIndexChanged(const QString &arg1);

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_23_clicked();

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_pushButton_24_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_20_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

