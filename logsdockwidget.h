#ifndef LOGSDOCKWIDGET_H
#define LOGSDOCKWIDGET_H

#include <QtWidgets>

class LogsDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit LogsDockWidget(QWidget *parent = nullptr);
    ~LogsDockWidget();

public slots:
    void on_closed();
    void on_opened();

private:
    QTableWidget* tableWidget;
};

#endif // LOGSDOCKWIDGET_H
