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
    void startSave(QVector<QString> values, int startYear, int endYear);

private slots:
    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_pushButton_clicked();

private:
    Ui::SaveToPdfDialog *ui;
};

#endif // SAVETOPDFDIALOG_H
