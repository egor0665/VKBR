#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QVector>
#include <UnitComparator.h>
#include <dbChangeValue.h>
#include <mainmodel.h>
#include <predictionModel.h>
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
    UnitComparator comparator;
    QTreeWidgetItem *addTreeRoot(QString name);
protected:
    QDoubleSpinBox *maxPayloadField;
    QDoubleSpinBox *minPayloadField;
    QDoubleSpinBox *weightField;
    QTextEdit *physInfoField;
    QTextEdit *econInfoField;

    void buildDisplayTab();
    void buildCompareTab();
    void buildAddUnitTab();
    void rebuildCompareTable(QString unitName1, QString unitName2);
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
private slots:
    void on_treeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_tableWidget_4_cellDoubleClicked(int row, int column);

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_pushButton_8_clicked();

    void on_tableWidget_6_itemChanged(QTableWidgetItem *item);

    void on_pushButton_2_clicked();

    void on_comboBoxUnitClass_currentIndexChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_comboBox_5_currentIndexChanged(const QString &arg1);

    void on_pushButton_11_clicked();

    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_comboBox_6_currentIndexChanged(const QString &arg1);

    void on_comboBox_7_currentIndexChanged(const QString &arg1);

    void on_comboBox_8_currentIndexChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

