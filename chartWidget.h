#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QtCharts/QAbstractAxis>
#include <QtCharts/qpolarchart.h>
#include <QtCharts/QtCharts>

namespace Ui {
class chartWidget;
}

class chartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit chartWidget(QWidget *parent = nullptr, QPolarChart *chart = nullptr);
    ~chartWidget();

private:
    Ui::chartWidget *ui;
};

#endif // CHARTWIDGET_H
