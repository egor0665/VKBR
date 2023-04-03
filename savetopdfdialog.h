#ifndef SAVETOPDFDIALOG_H
#define SAVETOPDFDIALOG_H

#include <QDialog>
#include <QListWidget>

namespace Ui {
class SaveToPdfDialog;
}

class SaveToPdfDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveToPdfDialog(QWidget *parent = nullptr);
    ~SaveToPdfDialog();

Q_SIGNALS:
    void startSave(QString name, QVector<QString> values, QVector<QString> chartValues, int startYear, int endYear);

private slots:
    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::SaveToPdfDialog *ui;
};

#endif // SAVETOPDFDIALOG_H
