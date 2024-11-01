#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include <QtSvg>
#include <QtXml>

#include "operationsdockwidget.h"
#include "stationsdockwidget.h"
#include "logsdockwidget.h"

namespace Ui {
class MainWindow;
}

class SvgItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    SvgItem* findItem(QString id);
    static MainWindow* instance;

public slots:
    void on_buttonClicked(int id);
    void on_itemOpened(QString text);
    void on_itemClosed(QString text);
    void on_transformer1CloseAll();
    void on_transformer2CloseAll();
    void on_openAllItems();
    void about();

private:
    void viewAll();
    void viewNotr1();
    void viewNotr2();
    void viewStation1();
    void viewStation2();
    void viewStation3();
    void viewStation4();
    void viewStation5();
    void viewTransformer1();
    void viewTransformer2();

    void setupDocument();
    void setupRenderer();
    void setupScene();

    void setupNotr1();
    void setupNotr2();
    void setupStation1();
    void setupStation2();
    void setupStation3();
    void setupStation4();
    void setupStation5();
    void setupTransformer1();
    void setupTransformer2();

    void setupNotr1Connections();
    void setupNotr2Connections();
    void setupStation1Connections();
    void setupStation2Connections();
    void setupStation3Connections();
    void setupStation4Connections();
    void setupStation5Connections();
    void setupTransformer1Connections();
    void setupTransformer2Connections();

    void setupDockWidgets();
    void setupActions();
    void setupSignalsSlots();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    OperationsDockWidget* operations;
    LogsDockWidget* logs;
    StationsDockWidget* stations;

    QSvgRenderer* renderer;
    QDomDocument* document;
    QString svgFilename;
};

#endif // MAINWINDOW_H
