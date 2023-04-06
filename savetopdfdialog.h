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

    void closeEvent(QCloseEvent *);
    void init();
Q_SIGNALS:
    void startSave(QString name, QVector<QString> values, QVector<QPair<QVector<QString>,QString>> chartValues, int startYear, int endYear);
    void saveToPdfDialogClosed();
private slots:
    void on_listWidget_itemChanged(QListWidgetItem *item);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tabWidget_tabCloseRequested(int index);

private:
    Ui::SaveToPdfDialog *ui;
};

#endif // SAVETOPDFDIALOG_H
