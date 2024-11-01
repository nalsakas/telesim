#ifndef STATIONSDOCKWIDGET_H
#define STATIONSDOCKWIDGET_H

#include <QtWidgets>

class StationsDockWidget : public QDockWidget
{
    Q_OBJECT

public:
     enum Button {ALL,NOTR1, STATION1, TRANSFORMER1, STATION2, STATION3, NOTR2, STATION4, TRANSFORMER2, STATION5};
    StationsDockWidget(QWidget *parent = nullptr);

signals:
    void buttonClicked(int);

private:
    QButtonGroup* group;
};

#endif // STATIONSDOCKWIDGET_H
