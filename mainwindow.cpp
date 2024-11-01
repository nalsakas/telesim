#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "svgitem.h"
#include "asvgitem.h"
#include "yasvgitem.h"
#include "masvgitem.h"
#include "ksvgitem.h"
#include "gtsvgitem.h"
#include "ystsvgitem.h"
#include "railsvgitem.h"
#include "linesvgitem.h"
#include "textsvgitem.h"
#include "boxsvgitem.h"
#include "aboutdialog.h"

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    instance = this;

    ui->setupUi(this);
    setCentralWidget(ui->graphicsView);

    setupDocument();
    setupRenderer();
    setupScene();
    setupDockWidgets();

    setupNotr1();
    setupNotr2();
    setupStation1();
    setupStation2();
    setupStation3();
    setupStation4();
    setupStation5();
    setupTransformer1();
    setupTransformer2();

    setupNotr1Connections();
    setupNotr2Connections();
    setupStation1Connections();
    setupStation2Connections();
    setupStation3Connections();
    setupStation4Connections();
    setupStation5Connections();
    setupTransformer1Connections();
    setupTransformer2Connections();

    setupActions();
    setupSignalsSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete document;
}

void MainWindow::on_buttonClicked(int id)
{
    switch (id) {
    case StationsDockWidget::ALL:
        viewAll();
        break;
    case StationsDockWidget::NOTR1:
        viewNotr1();
        break;
    case StationsDockWidget::NOTR2:
        viewNotr2();
        break;
    case StationsDockWidget::STATION1:
        viewStation1();
        break;
    case StationsDockWidget::STATION2:
        viewStation2();
        break;
    case StationsDockWidget::STATION3:
        viewStation3();
        break;
    case StationsDockWidget::STATION4:
        viewStation4();
        break;
    case StationsDockWidget::STATION5:
        viewStation5();
        break;
    case StationsDockWidget::TRANSFORMER1:
        viewTransformer1();
        break;
    case StationsDockWidget::TRANSFORMER2:
        viewTransformer2();
        break;
    }
}

void MainWindow::on_itemOpened(QString text)
{
    bool found = false;

    foreach (QGraphicsItem* gItem, scene->items())
    {
        SvgItem* svgItem = dynamic_cast<SvgItem*>(gItem);
        if (svgItem && svgItem->elementId() == text)
        {
            svgItem->open();
            found = true;
        }
    }

    if (!found) {
        qDebug() <<  text << " bulunamadı.";
    }
}

void MainWindow::on_itemClosed(QString text)
{
    bool found = false;
    foreach (QGraphicsItem* gItem, scene->items())
    {
        SvgItem* svgItem = dynamic_cast<SvgItem*>(gItem);
        if (svgItem && svgItem->elementId() == text)
        {
            svgItem->close();
            found = true;
        }
    }

    if (!found) {
        qDebug() <<  text << " bulunamadı.";
    }
}

void MainWindow::on_transformer1CloseAll()
{
    findItem("transformer1_box")->setClosed(true);
    findItem("transformer1_a")->setClosed(true);
    findItem("transformer1_a1")->setClosed(true);
    findItem("transformer1_a2")->setClosed(true);
    findItem("transformer1_k1")->setClosed(true);
    findItem("transformer1_k2")->setClosed(true);
    findItem("transformer1_k10")->setClosed(true);
    findItem("transformer1_k20")->setClosed(true);
    findItem("transformer1_a10")->setClosed(true);
    findItem("transformer1_a20")->setClosed(true);
    findItem("transformer1_ayst1")->setClosed(true);
    findItem("transformer1_ayst2")->setClosed(true);
    findItem("transformer1_ke1")->setClosed(true);
    findItem("transformer1_kb1")->setClosed(true);
    findItem("transformer1_ae1")->setClosed(true);
    findItem("transformer1_ab1")->setClosed(true);

    operations->reload();

    QTimer::singleShot(0, this, [=]{
        QProgressBar bar;
        bar.setRange(0,0);
        bar.setMaximumHeight(statusBar()->height() - 10);
        statusBar()->addWidget(&bar);

        findItem("transformer1_box")->powerOff();
        findItem("transformer2_box")->powerOff();
        findItem("transformer1_box")->powerOn();
        findItem("transformer2_box")->powerOn();
        statusBar()->removeWidget(&bar);
    });
}

void MainWindow::on_transformer2CloseAll()
{
    findItem("transformer2_box")->setClosed(true);
    findItem("transformer2_a")->setClosed(true);
    findItem("transformer2_a1")->setClosed(true);
    findItem("transformer2_a2")->setClosed(true);
    findItem("transformer2_k1")->setClosed(true);
    findItem("transformer2_k2")->setClosed(true);
    findItem("transformer2_k10")->setClosed(true);
    findItem("transformer2_k20")->setClosed(true);
    findItem("transformer2_a10")->setClosed(true);
    findItem("transformer2_a20")->setClosed(true);
    findItem("transformer2_ayst1")->setClosed(true);
    findItem("transformer2_ayst2")->setClosed(true);
    findItem("transformer2_ke1")->setClosed(true);
    findItem("transformer2_kb1")->setClosed(true);
    findItem("transformer2_ae1")->setClosed(true);
    findItem("transformer2_ab1")->setClosed(true);

    operations->reload();

    QTimer::singleShot(0, this, [=]{
        QProgressBar bar;
        bar.setRange(0,0);
        bar.setMaximumHeight(statusBar()->height() - 10);
        statusBar()->addWidget(&bar);

        findItem("transformer1_box")->powerOff();
        findItem("transformer2_box")->powerOff();
        findItem("transformer2_box")->powerOn();
        findItem("transformer1_box")->powerOn();
        statusBar()->removeWidget(&bar);
    });
}

void MainWindow::on_openAllItems()
{
    QProgressBar bar;
    bar.setRange(0,0);
    statusBar()->addWidget(&bar);

    findItem("transformer1_box")->powerOff();
    findItem("transformer2_box")->powerOff();

    foreach (QGraphicsItem* gItem, scene->items())
    {
        SvgItem* svgItem = dynamic_cast<SvgItem*>(gItem);

        if (svgItem && svgItem->isClosed())
        {
            svgItem->setClosed(false);
        }
        QApplication::processEvents();
    }

    operations->reload();
    statusBar()->removeWidget(&bar);
}

void MainWindow::about()
{
    AboutDialog dialog(this);
    dialog.exec();
}

void MainWindow::viewAll()
{
    ui->graphicsView->resetMatrix();

    double scaleNum = qMin(ui->graphicsView->width() / scene->sceneRect().width(), ui->graphicsView->height() / scene->sceneRect().height());
    scaleNum *= .9;
    ui->graphicsView->scale( scaleNum, scaleNum);
    ui->graphicsView->centerOn(scene->sceneRect().center());
}

void MainWindow::viewNotr1()
{
    ui->graphicsView->resetMatrix();

    double scaleNum = qMin(ui->graphicsView->width() / findItem("notr1")->boundingRect().width(), ui->graphicsView->height() / findItem("notr1")->boundingRect().height());
    scaleNum *= .9;

    ui->graphicsView->scale( scaleNum, scaleNum);
    ui->graphicsView->centerOn( findItem("notr1")->mapToScene( findItem("notr1")->boundingRect().center() ) );
}

void MainWindow::viewStation1()
{
    ui->graphicsView->resetMatrix();

    double scaleNum = qMin(ui->graphicsView->width() / findItem("station1")->boundingRect().width(), ui->graphicsView->height() / findItem("station1")->boundingRect().height());
    scaleNum *= .9;

    ui->graphicsView->scale( scaleNum, scaleNum);
    ui->graphicsView->centerOn( findItem("station1")->mapToScene( findItem("station1")->boundingRect().center()));
}

void MainWindow::viewTransformer1()
{
    ui->graphicsView->resetMatrix();

    double scaleNum = qMin(ui->graphicsView->width() / findItem("transformer1")->boundingRect().width(), ui->graphicsView->height() / findItem("transformer1")->boundingRect().height());
    scaleNum *= .9;

    ui->graphicsView->scale( scaleNum, scaleNum);
    ui->graphicsView->centerOn( findItem("transformer1")->mapToScene( findItem("transformer1")->boundingRect().center()));
}

void MainWindow::viewStation2()
{
    ui->graphicsView->resetMatrix();

    double scaleNum = qMin(ui->graphicsView->width() / findItem("station2")->boundingRect().width(), ui->graphicsView->height() / findItem("station2")->boundingRect().height());
    scaleNum *= .9;

    ui->graphicsView->scale( scaleNum, scaleNum);
    ui->graphicsView->centerOn( findItem("station2")->mapToScene( findItem("station2")->boundingRect().center()));
}

void MainWindow::viewStation3()
{
    ui->graphicsView->resetMatrix();

    double scaleNum = qMin(ui->graphicsView->width() / findItem("station3")->boundingRect().width(), ui->graphicsView->height() / findItem("station3")->boundingRect().height());
    scaleNum *= .9;

    ui->graphicsView->scale( scaleNum, scaleNum);
    ui->graphicsView->centerOn( findItem("station3")->mapToScene(findItem("station3")->boundingRect().center()));
}

void MainWindow::viewNotr2()
{
    ui->graphicsView->resetMatrix();

    double scaleNum = qMin(ui->graphicsView->width() / findItem("notr2")->boundingRect().width(), ui->graphicsView->height() / findItem("notr2")->boundingRect().height());
    scaleNum *= .9;

    ui->graphicsView->scale( scaleNum, scaleNum);
    ui->graphicsView->centerOn( findItem("notr2")->mapToScene(findItem("notr2")->boundingRect().center()));
}

void MainWindow::viewStation4()
{
    ui->graphicsView->resetMatrix();

    double scaleNum = qMin(ui->graphicsView->width() / findItem("station4")->boundingRect().width(), ui->graphicsView->height() / findItem("station4")->boundingRect().height());
    scaleNum *= .9;

    ui->graphicsView->scale( scaleNum, scaleNum);
    ui->graphicsView->centerOn( findItem("station4")->mapToScene(findItem("station4")->boundingRect().center()));
}

void MainWindow::viewStation5()
{
    ui->graphicsView->resetMatrix();

    double scaleNum = qMin(ui->graphicsView->width() / findItem("station5")->boundingRect().width(), ui->graphicsView->height() / findItem("station5")->boundingRect().height());
    scaleNum *= .9;

    ui->graphicsView->scale( scaleNum, scaleNum);
    ui->graphicsView->centerOn( findItem("station5")->mapToScene( findItem("station5")->boundingRect().center()));
}

void MainWindow::viewTransformer2()
{
    ui->graphicsView->resetMatrix();

    double scaleNum = qMin(ui->graphicsView->width() / findItem("transformer2")->boundingRect().width(), ui->graphicsView->height() / findItem("transformer2")->boundingRect().height());
    scaleNum *= .9;

    ui->graphicsView->scale( scaleNum, scaleNum);
    ui->graphicsView->centerOn( findItem("transformer2")->mapToScene(findItem("transformer2")->boundingRect().center()));
}

void MainWindow::setupDocument()
{
    svgFilename = QDir::currentPath() + "/map.svg";

    QFile file(svgFilename);
    if (!file.open(QIODevice::ReadOnly))
    {
        qDebug() << QString("Open file (%1) failed.").arg(svgFilename);
    }

    if (!file.isReadable())
    {
        qDebug() << QString("Read file (%1) failed.").arg(svgFilename);
    }

    document = new QDomDocument();
    document->setContent(file.readAll());
}

void MainWindow::setupRenderer()
{
    renderer = new QSvgRenderer(svgFilename, this);

    if (!renderer->isValid())
    {
        qDebug() << "Renderer is not valid.";
    }
}

void MainWindow::setupScene()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
}

void MainWindow::setupNotr1()
{
    SvgItem*
    item = new TEXTSvgItem(document, renderer,"notr1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr1_title");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "notr1_yst");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr1_ystlabel");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "notr1_gt1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr1_gt1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "notr1_v1");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "notr1_ya1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr1_ya1label");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "notr1_ya2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr1_ya2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "notr1_v3");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "notr1_gt2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr1_gt2label");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "notr1_l1");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "notr1_l2");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "notr1_l3");
    scene->addItem(item);
}

void MainWindow::setupNotr2()
{
    SvgItem *
    item = new TEXTSvgItem(document, renderer, "notr2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr2_title");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "notr2_yst");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr2_ystlabel");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "notr2_gt1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr2_gt1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "notr2_v1");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "notr2_ya1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr2_ya1label");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "notr2_ya2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr2_ya2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "notr2_v3");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "notr2_gt2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "notr2_gt2label");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "notr2_l2");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "notr2_l3");
    scene->addItem(item);
}

void MainWindow::setupStation1()
{
    SvgItem *
    item = new TEXTSvgItem(document, renderer, "station1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_title");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station1_v1");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station1_ae");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_aelabel");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station1_gte");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_gtelabel");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station1_yae");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_yaelabel");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_ae2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_ae2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station1_v2");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "station1_yst");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_ystlabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station1_h1");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station1_v3");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "station1_ma1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_ma1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station1_v4");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station1_gtm");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_gtmlabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station1_v5");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station1_ya1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_ya1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station1_v6");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station1_gt1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_gt1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station1_v7");
    scene->addItem(item);

    item = new YASvgItem(document, renderer,"station1_ya2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_ya2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station1_v8");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station1_gt2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_gt2label");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station1_yab");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_yablabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station1_v9");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station1_ab");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_ablabel");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station1_a1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station1_a1label");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station1_l1");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station1_l2");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station1_l3");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station1_l4");
    scene->addItem(item);
}

void MainWindow::setupStation2()
{
    SvgItem *
    item = new TEXTSvgItem(document, renderer, "station2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_title");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station2_v1");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station2_ae");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_aelabel");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station2_gte");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_gtelabel");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station2_yae");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_yaelabel");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_ae2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_ae2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station2_v2");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "station2_yst");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_ystlabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station2_h1");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station2_v3");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "station2_ma1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_ma1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station2_v4");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station2_gtm");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_gtmlabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station2_v5");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station2_ya1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_ya1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station2_v6");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station2_gt1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_gt1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station2_v7");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station2_ya2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_ya2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station2_v8");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station2_gt2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_gt2label");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station2_yab");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_yablabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station2_v9");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station2_ab");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_ablabel");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station2_a1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station2_a1label");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station2_l1");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station2_l2");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station2_l3");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station2_l4");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station2_l5");
    scene->addItem(item);
}

void MainWindow::setupStation3()
{
    SvgItem *
    item = new TEXTSvgItem(document, renderer, "station3");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_title");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station3_v1");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station3_ae");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_aelabel");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station3_gte");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_gtelabel");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station3_yae");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_yaelabel");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_ae2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_ae2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station3_v2");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "station3_yst");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_ystlabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station3_h1");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station3_v3");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "station3_ma1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_ma1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station3_v4");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station3_gtm");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_gtmlabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station3_v5");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station3_ya1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_ya1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station3_v6");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station3_gt1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_gt1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station3_v7");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station3_ya2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_ya2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station3_v8");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station3_gt2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_gt2label");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station3_yab");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_yablabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station3_v9");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station3_ab");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_ablabel");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station3_a1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station3_a1label");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station3_l1");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station3_l2");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station3_l3");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station3_l4");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station3_l5");
    scene->addItem(item);
}

void MainWindow::setupStation4()
{
    SvgItem *
    item = new TEXTSvgItem(document, renderer, "station4");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_title");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station4_v1");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station4_ae");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_aelabel");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station4_gte");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_gtelabel");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station4_yae");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_yaelabel");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_ae2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_ae2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station4_v2");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "station4_yst");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_ystlabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station4_h1");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station4_v3");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "station4_ma1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_ma1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station4_v4");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station4_gtm");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_gtmlabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station4_v5");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station4_ya1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_ya1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station4_v6");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station4_gt1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_gt1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station4_v7");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station4_ya2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_ya2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station4_v8");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station4_gt2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_gt2label");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station4_yab");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_yablabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station4_v9");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station4_ab");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_ablabel");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station4_a1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station4_a1label");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station4_l1");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station4_l2");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station4_l3");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station4_l4");
    scene->addItem(item);
}

void MainWindow::setupStation5()
{
    SvgItem *
    item = new TEXTSvgItem(document, renderer, "station5");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_title");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station5_v1");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station5_ae");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_aelabel");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station5_gte");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_gtelabel");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station5_yae");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_yaelabel");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_ae2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_ae2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station5_v2");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "station5_yst");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_ystlabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station5_h1");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station5_v3");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "station5_ma1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_ma1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station5_v4");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station5_gtm");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_gtmlabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station5_v5");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station5_ya1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_ya1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station5_v6");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station5_gt1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_gt1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station5_v7");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station5_ya2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_ya2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station5_v8");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "station5_gt2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_gt2label");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "station5_yab");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_yablabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "station5_v9");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station5_ab");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_ablabel");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "station5_a1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "station5_a1label");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station5_l1");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station5_l2");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station5_l3");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station5_l4");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "station5_l5");
    scene->addItem(item);
}

void MainWindow::setupTransformer1()
{
    SvgItem *
    item = new TEXTSvgItem(document, renderer, "transformer1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_title");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v1");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "transformer1_gte1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_gte1label");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer1_ae1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_ae1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v2");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer1_ke1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_ke1label");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "transformer1_yst1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_yst1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_h1");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer1_ayst1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_ayst1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v3");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "transformer1_yap");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_yaplabel");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "transformer1_a10");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_a10label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v4");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "transformer1_gt10");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_gt10label");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer1_k10");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_k10label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v5");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "transformer1_myst1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_myst1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v6");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer1_k1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_k1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v7");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer1_a1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_a1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_h2");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer1_a");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_alabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v8");
    scene->addItem(item);

    item = new BOXSvgItem(document, renderer, "transformer1_box");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_boxlabel");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer1_a2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_a2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v9");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer1_k2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_k2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v10");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "transformer1_myst2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_myst2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v11");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer1_k20");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_k20label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v12");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "transformer1_gt20");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_gt20label");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "transformer1_a20");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_a20label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v13");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer1_ayst2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_ayst2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_h3");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "transformer1_yst2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_yst2label");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer1_kb1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_kb1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v14");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer1_ab1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_ab1label");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "transformer1_gtb1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_gtb1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer1_v15");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "transformer1_yan1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_yan1label");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "transformer1_yan2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer1_yan2label");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "transformer1_l1");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "transformer1_l2");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "transformer1_l3");
    scene->addItem(item);
}

void MainWindow::setupTransformer2()
{
    SvgItem *
    item = new TEXTSvgItem(document, renderer, "transformer2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_title");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v1");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "transformer2_gte1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_gte1label");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer2_ae1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_ae1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v2");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer2_ke1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_ke1label");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "transformer2_yst1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_yst1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_h1");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer2_ayst1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_ayst1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v3");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "transformer2_yap");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_yaplabel");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "transformer2_a10");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_a10label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v4");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "transformer2_gt10");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_gt10label");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer2_k10");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_k10label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v5");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "transformer2_myst1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_myst1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v6");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer2_k1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_k1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v7");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer2_a1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_a1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_h2");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer2_a");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_alabel");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v8");
    scene->addItem(item);

    item = new BOXSvgItem(document, renderer, "transformer2_box");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_boxlabel");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer2_a2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_a2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v9");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer2_k2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_k2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v10");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "transformer2_myst2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_myst2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v11");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer2_k20");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_k20label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v12");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "transformer2_gt20");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_gt20label");
    scene->addItem(item);

    item = new ASvgItem(document, renderer, "transformer2_a20");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_a20label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v13");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer2_ayst2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_ayst2label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_h3");
    scene->addItem(item);

    item = new YSTSvgItem(document, renderer, "transformer2_yst2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_yst2label");
    scene->addItem(item);

    item = new KSvgItem(document, renderer, "transformer2_kb1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_kb1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v14");
    scene->addItem(item);

    item = new MASvgItem(document, renderer, "transformer2_ab1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_ab1label");
    scene->addItem(item);

    item = new GTSvgItem(document, renderer, "transformer2_gtb1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_gtb1label");
    scene->addItem(item);

    item = new LINESvgItem(document, renderer, "transformer2_v15");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "transformer2_yan1");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_yan1label");
    scene->addItem(item);

    item = new YASvgItem(document, renderer, "transformer2_yan2");
    scene->addItem(item);

    item = new TEXTSvgItem(document, renderer, "transformer2_yan2label");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer,"transformer2_l1");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "transformer2_l2");
    scene->addItem(item);

    item = new RAILSvgItem(document, renderer, "transformer2_l3");
    scene->addItem(item);
}

void MainWindow::setupNotr1Connections()
{
    // rigt to left
    findItem("notr1_l1")->addContact(findItem("notr1_v1"));
    findItem("notr1_v1")->addContact(findItem("notr1_l1"));

    findItem("notr1_v1")->addContact(findItem("notr1_gt1"));

    findItem("notr1_v1")->addContact(findItem("notr1_yst"));

    findItem("notr1_v1")->addContact(findItem("notr1_ya1"));
    findItem("notr1_ya1")->addContact(findItem("notr1_v1"));

    findItem("notr1_ya1")->addContact(findItem("notr1_l2"));
    findItem("notr1_l2")->addContact(findItem("notr1_ya1"));

    findItem("notr1_l2")->addContact(findItem("notr1_ya2"));
    findItem("notr1_ya2")->addContact(findItem("notr1_l2"));

    findItem("notr1_ya2")->addContact(findItem("notr1_v3"));
    findItem("notr1_v3")->addContact(findItem("notr1_ya2"));

    findItem("notr1_v3")->addContact(findItem("notr1_gt2"));

    findItem("notr1_v3")->addContact(findItem("notr1_l3"));
    findItem("notr1_l3")->addContact(findItem("notr1_v3"));
}

void MainWindow::setupNotr2Connections()
{
    // rigt to left
    findItem("station3_l5")->addContact(findItem("notr2_v1"));
    findItem("notr2_v1")->addContact(findItem("station3_l5"));

    findItem("notr2_v1")->addContact(findItem("notr2_gt1"));

    findItem("notr2_v1")->addContact(findItem("notr2_yst"));

    findItem("notr2_v1")->addContact(findItem("notr2_ya1"));
    findItem("notr2_ya1")->addContact(findItem("notr2_v1"));

    findItem("notr2_ya1")->addContact(findItem("notr2_l2"));
    findItem("notr2_l2")->addContact(findItem("notr2_ya1"));

    findItem("notr2_l2")->addContact(findItem("notr2_ya2"));
    findItem("notr2_ya2")->addContact(findItem("notr2_l2"));

    findItem("notr2_ya2")->addContact(findItem("notr2_v3"));
    findItem("notr2_v3")->addContact(findItem("notr2_ya2"));

    findItem("notr2_v3")->addContact(findItem("notr2_gt2"));

    findItem("notr2_v3")->addContact(findItem("notr2_l3"));
    findItem("notr2_l3")->addContact(findItem("notr2_v3"));
}

void MainWindow::setupStation1Connections()
{
    // top
    findItem("station1_yst")->addContact(findItem("station1_v2"));
    findItem("station1_v2")->addContact(findItem("station1_yst"));

    findItem("station1_v2")->addContact(findItem("station1_ae2"));
    findItem("station1_ae2")->addContact(findItem("station1_v2"));

    findItem("station1_ae2")->addContact(findItem("station1_h1"));
    findItem("station1_h1")->addContact(findItem("station1_ae2"));

    // left 1
    findItem("station1_h1")->addContact(findItem("station1_yae"));
    findItem("station1_yae")->addContact(findItem("station1_h1"));

    findItem("station1_yae")->addContact(findItem("station1_v1"));
    findItem("station1_v1")->addContact(findItem("station1_yae"));

    findItem("station1_v1")->addContact(findItem("station1_gte"));

    findItem("station1_v1")->addContact(findItem("station1_ae"));
    findItem("station1_ae")->addContact(findItem("station1_v1"));

    findItem("station1_v1")->addContact(findItem("notr1_l3"));
    findItem("notr1_l3")->addContact(findItem("station1_v1"));

    // left 2
    findItem("station1_h1")->addContact(findItem("station1_v3"));
    findItem("station1_v3")->addContact(findItem("station1_h1"));

    findItem("station1_v3")->addContact(findItem("station1_ma1"));
    findItem("station1_ma1")->addContact(findItem("station1_v3"));

    findItem("station1_ma1")->addContact(findItem("station1_v4"));
    findItem("station1_v4")->addContact(findItem("station1_ma1"));

    findItem("station1_v4")->addContact(findItem("station1_gtm"));

    findItem("station1_v4")->addContact(findItem("station1_l2"));
    findItem("station1_l2")->addContact(findItem("station1_v4"));

    // left 3
    findItem("station1_h1")->addContact(findItem("station1_v5"));
    findItem("station1_v5")->addContact(findItem("station1_h1"));

    findItem("station1_v5")->addContact(findItem("station1_ya1"));
    findItem("station1_ya1")->addContact(findItem("station1_v5"));

    findItem("station1_ya1")->addContact(findItem("station1_v6"));
    findItem("station1_v6")->addContact(findItem("station1_ya1"));

    findItem("station1_v6")->addContact(findItem("station1_gt1"));

    findItem("station1_v6")->addContact(findItem("station1_l1"));
    findItem("station1_l1")->addContact(findItem("station1_v6"));

    // left 4
    findItem("station1_h1")->addContact(findItem("station1_v7"));
    findItem("station1_v7")->addContact(findItem("station1_h1"));

    findItem("station1_v7")->addContact(findItem("station1_ya2"));
    findItem("station1_ya2")->addContact(findItem("station1_v7"));

    findItem("station1_ya2")->addContact(findItem("station1_v8"));
    findItem("station1_v8")->addContact(findItem("station1_ya2"));

    findItem("station1_v8")->addContact(findItem("station1_gt2"));

    findItem("station1_v8")->addContact(findItem("station1_l3"));
    findItem("station1_l3")->addContact(findItem("station1_v8"));

    // left 5
    findItem("station1_h1")->addContact(findItem("station1_yab"));
    findItem("station1_yab")->addContact(findItem("station1_h1"));

    findItem("station1_yab")->addContact(findItem("station1_v9"));
    findItem("station1_v9")->addContact(findItem("station1_yab"));

    findItem("station1_v9")->addContact(findItem("station1_ab"));
    findItem("station1_ab")->addContact(findItem("station1_v9"));

    findItem("station1_v9")->addContact(findItem("transformer1_l1"));
    findItem("transformer1_l1")->addContact(findItem("station1_v9"));

    // bottom
    findItem("station1_ae")->addContact(findItem("station1_l1"));
    findItem("station1_l1")->addContact(findItem("station1_ae"));

    findItem("station1_l1")->addContact(findItem("station1_a1"));
    findItem("station1_a1")->addContact(findItem("station1_l1"));

    findItem("station1_a1")->addContact(findItem("station1_l4"));
    findItem("station1_l4")->addContact(findItem("station1_a1"));

     findItem("station1_l4")->addContact(findItem("station1_ab"));
      findItem("station1_ab")->addContact(findItem("station1_l4"));
}

void MainWindow::setupStation2Connections()
{
    // top
    findItem("station2_yst")->addContact(findItem("station2_v2"));
    findItem("station2_v2")->addContact(findItem("station2_yst"));

    findItem("station2_v2")->addContact(findItem("station2_ae2"));
    findItem("station2_ae2")->addContact(findItem("station2_v2"));

    findItem("station2_ae2")->addContact(findItem("station2_h1"));
    findItem("station2_h1")->addContact(findItem("station2_ae2"));

    // left 1
    findItem("station2_h1")->addContact(findItem("station2_yae"));
    findItem("station2_yae")->addContact(findItem("station2_h1"));

    findItem("station2_yae")->addContact(findItem("station2_v1"));
    findItem("station2_v1")->addContact(findItem("station2_yae"));

    findItem("station2_v1")->addContact(findItem("station2_gte"));

    findItem("station2_v1")->addContact(findItem("station2_ae"));
    findItem("station2_ae")->addContact(findItem("station2_v1"));

    findItem("station2_v1")->addContact(findItem("transformer1_l3"));
    findItem("transformer1_l3")->addContact(findItem("station2_v1"));

    // left 2
    findItem("station2_h1")->addContact(findItem("station2_v3"));
    findItem("station2_v3")->addContact(findItem("station2_h1"));

    findItem("station2_v3")->addContact(findItem("station2_ma1"));
    findItem("station2_ma1")->addContact(findItem("station2_v3"));

    findItem("station2_ma1")->addContact(findItem("station2_v4"));
    findItem("station2_v4")->addContact(findItem("station2_ma1"));

    findItem("station2_v4")->addContact(findItem("station2_gtm"));

    findItem("station2_v4")->addContact(findItem("station2_l2"));
    findItem("station2_l2")->addContact(findItem("station2_v4"));

    // left 3
    findItem("station2_h1")->addContact(findItem("station2_v5"));
    findItem("station2_v5")->addContact(findItem("station2_h1"));

    findItem("station2_v5")->addContact(findItem("station2_ya1"));
    findItem("station2_ya1")->addContact(findItem("station2_v5"));

    findItem("station2_ya1")->addContact(findItem("station2_v6"));
    findItem("station2_v6")->addContact(findItem("station2_ya1"));

    findItem("station2_v6")->addContact(findItem("station2_gt1"));

    findItem("station2_v6")->addContact(findItem("station2_l1"));
    findItem("station2_l1")->addContact(findItem("station2_v6"));

    // left 4
    findItem("station2_h1")->addContact(findItem("station2_v7"));
    findItem("station2_v7")->addContact(findItem("station2_h1"));

    findItem("station2_v7")->addContact(findItem("station2_ya2"));
    findItem("station2_ya2")->addContact(findItem("station2_v7"));

    findItem("station2_ya2")->addContact(findItem("station2_v8"));
    findItem("station2_v8")->addContact(findItem("station2_ya2"));

    findItem("station2_v8")->addContact(findItem("station2_gt2"));

    findItem("station2_v8")->addContact(findItem("station2_l3"));
    findItem("station2_l3")->addContact(findItem("station2_v8"));

    // left 5
    findItem("station2_h1")->addContact(findItem("station2_yab"));
    findItem("station2_yab")->addContact(findItem("station2_h1"));

    findItem("station2_yab")->addContact(findItem("station2_v9"));
    findItem("station2_v9")->addContact(findItem("station2_yab"));

    findItem("station2_v9")->addContact(findItem("station2_ab"));
    findItem("station2_ab")->addContact(findItem("station2_v9"));

    findItem("station2_v9")->addContact(findItem("station2_l5"));
    findItem("station2_l5")->addContact(findItem("station2_v9"));

    // bottom
    findItem("station2_ae")->addContact(findItem("station2_l1"));
    findItem("station2_l1")->addContact(findItem("station2_ae"));

    findItem("station2_l1")->addContact(findItem("station2_a1"));
    findItem("station2_a1")->addContact(findItem("station2_l1"));

    findItem("station2_a1")->addContact(findItem("station2_l4"));
    findItem("station2_l4")->addContact(findItem("station2_a1"));

    findItem("station2_l4")->addContact(findItem("station2_ab"));
    findItem("station2_ab")->addContact(findItem("station2_l4"));
}

void MainWindow::setupStation3Connections()
{
    // top
    findItem("station3_yst")->addContact(findItem("station3_v2"));
    findItem("station3_v2")->addContact(findItem("station3_yst"));

    findItem("station3_v2")->addContact(findItem("station3_ae2"));
    findItem("station3_ae2")->addContact(findItem("station3_v2"));

    findItem("station3_ae2")->addContact(findItem("station3_h1"));
    findItem("station3_h1")->addContact(findItem("station3_ae2"));

    // left 1
    findItem("station3_h1")->addContact(findItem("station3_yae"));
    findItem("station3_yae")->addContact(findItem("station3_h1"));

    findItem("station3_yae")->addContact(findItem("station3_v1"));
    findItem("station3_v1")->addContact(findItem("station3_yae"));

    findItem("station3_v1")->addContact(findItem("station3_gte"));

    findItem("station3_v1")->addContact(findItem("station3_ae"));
    findItem("station3_ae")->addContact(findItem("station3_v1"));

    findItem("station3_v1")->addContact(findItem("station2_l5"));
    findItem("station2_l5")->addContact(findItem("station3_v1"));

    // left 2
    findItem("station3_h1")->addContact(findItem("station3_v3"));
    findItem("station3_v3")->addContact(findItem("station3_h1"));

    findItem("station3_v3")->addContact(findItem("station3_ma1"));
    findItem("station3_ma1")->addContact(findItem("station3_v3"));

    findItem("station3_ma1")->addContact(findItem("station3_v4"));
    findItem("station3_v4")->addContact(findItem("station3_ma1"));

    findItem("station3_v4")->addContact(findItem("station3_gtm"));

    findItem("station3_v4")->addContact(findItem("station3_l2"));
    findItem("station3_l2")->addContact(findItem("station3_v4"));

    // left 3
    findItem("station3_h1")->addContact(findItem("station3_v5"));
    findItem("station3_v5")->addContact(findItem("station3_h1"));

    findItem("station3_v5")->addContact(findItem("station3_ya1"));
    findItem("station3_ya1")->addContact(findItem("station3_v5"));

    findItem("station3_ya1")->addContact(findItem("station3_v6"));
    findItem("station3_v6")->addContact(findItem("station3_ya1"));

    findItem("station3_v6")->addContact(findItem("station3_gt1"));

    findItem("station3_v6")->addContact(findItem("station3_l1"));
    findItem("station3_l1")->addContact(findItem("station3_v6"));

    // left 4
    findItem("station3_h1")->addContact(findItem("station3_v7"));
    findItem("station3_v7")->addContact(findItem("station3_h1"));

    findItem("station3_v7")->addContact(findItem("station3_ya2"));
    findItem("station3_ya2")->addContact(findItem("station3_v7"));

    findItem("station3_ya2")->addContact(findItem("station3_v8"));
    findItem("station3_v8")->addContact(findItem("station3_ya2"));

    findItem("station3_v8")->addContact(findItem("station3_gt2"));

    findItem("station3_v8")->addContact(findItem("station3_l3"));
    findItem("station3_l3")->addContact(findItem("station3_v8"));

    // left 5
    findItem("station3_h1")->addContact(findItem("station3_yab"));
    findItem("station3_yab")->addContact(findItem("station3_h1"));

    findItem("station3_yab")->addContact(findItem("station3_v9"));
    findItem("station3_v9")->addContact(findItem("station3_yab"));

    findItem("station3_v9")->addContact(findItem("station3_ab"));
    findItem("station3_ab")->addContact(findItem("station3_v9"));

    findItem("station3_v9")->addContact(findItem("station3_l5"));
    findItem("station3_l5")->addContact(findItem("station3_v9"));

    // bottom
    findItem("station3_ae")->addContact(findItem("station3_l1"));
    findItem("station3_l1")->addContact(findItem("station3_ae"));

    findItem("station3_l1")->addContact(findItem("station3_a1"));
    findItem("station3_a1")->addContact(findItem("station3_l1"));

    findItem("station3_a1")->addContact(findItem("station3_l4"));
    findItem("station3_l4")->addContact(findItem("station3_a1"));

    findItem("station3_l4")->addContact(findItem("station3_ab"));
    findItem("station3_ab")->addContact(findItem("station3_l4"));
}

void MainWindow::setupStation4Connections()
{
    // top
    findItem("station4_yst")->addContact(findItem("station4_v2"));
    findItem("station4_v2")->addContact(findItem("station4_yst"));

    findItem("station4_v2")->addContact(findItem("station4_ae2"));
    findItem("station4_ae2")->addContact(findItem("station4_v2"));

    findItem("station4_ae2")->addContact(findItem("station4_h1"));
    findItem("station4_h1")->addContact(findItem("station4_ae2"));

    // left 1
    findItem("station4_h1")->addContact(findItem("station4_yae"));
    findItem("station4_yae")->addContact(findItem("station4_h1"));

    findItem("station4_yae")->addContact(findItem("station4_v1"));
    findItem("station4_v1")->addContact(findItem("station4_yae"));

    findItem("station4_v1")->addContact(findItem("station4_gte"));

    findItem("station4_v1")->addContact(findItem("station4_ae"));
    findItem("station4_ae")->addContact(findItem("station4_v1"));

    findItem("station4_v1")->addContact(findItem("notr2_l3"));
    findItem("notr2_l3")->addContact(findItem("station4_v1"));

    // left 2
    findItem("station4_h1")->addContact(findItem("station4_v3"));
    findItem("station4_v3")->addContact(findItem("station4_h1"));

    findItem("station4_v3")->addContact(findItem("station4_ma1"));
    findItem("station4_ma1")->addContact(findItem("station4_v3"));

    findItem("station4_ma1")->addContact(findItem("station4_v4"));
    findItem("station4_v4")->addContact(findItem("station4_ma1"));

    findItem("station4_v4")->addContact(findItem("station4_gtm"));

    findItem("station4_v4")->addContact(findItem("station4_l2"));
    findItem("station4_l2")->addContact(findItem("station4_v4"));

    // left 3
    findItem("station4_h1")->addContact(findItem("station4_v5"));
    findItem("station4_v5")->addContact(findItem("station4_h1"));

    findItem("station4_v5")->addContact(findItem("station4_ya1"));
    findItem("station4_ya1")->addContact(findItem("station4_v5"));

    findItem("station4_ya1")->addContact(findItem("station4_v6"));
    findItem("station4_v6")->addContact(findItem("station4_ya1"));

    findItem("station4_v6")->addContact(findItem("station4_gt1"));

    findItem("station4_v6")->addContact(findItem("station4_l1"));
    findItem("station4_l1")->addContact(findItem("station4_v6"));

    // left 4
    findItem("station4_h1")->addContact(findItem("station4_v7"));
    findItem("station4_v7")->addContact(findItem("station4_h1"));

    findItem("station4_v7")->addContact(findItem("station4_ya2"));
    findItem("station4_ya2")->addContact(findItem("station4_v7"));

    findItem("station4_ya2")->addContact(findItem("station4_v8"));
    findItem("station4_v8")->addContact(findItem("station4_ya2"));

    findItem("station4_v8")->addContact(findItem("station4_gt2"));

    findItem("station4_v8")->addContact(findItem("station4_l3"));
    findItem("station4_l3")->addContact(findItem("station4_v8"));

    // left 5
    findItem("station4_h1")->addContact(findItem("station4_yab"));
    findItem("station4_yab")->addContact(findItem("station4_h1"));

    findItem("station4_yab")->addContact(findItem("station4_v9"));
    findItem("station4_v9")->addContact(findItem("station4_yab"));

    findItem("station4_v9")->addContact(findItem("station4_ab"));
    findItem("station4_ab")->addContact(findItem("station4_v9"));

    findItem("station4_v9")->addContact(findItem("transformer2_l1"));
    findItem("transformer2_l1")->addContact(findItem("station4_v9"));

    // bottom
    findItem("station4_ae")->addContact(findItem("station4_l1"));
    findItem("station4_l1")->addContact(findItem("station4_ae"));

    findItem("station4_l1")->addContact(findItem("station4_a1"));
    findItem("station4_a1")->addContact(findItem("station4_l1"));

    findItem("station4_a1")->addContact(findItem("station4_l4"));
    findItem("station4_l4")->addContact(findItem("station4_a1"));

    findItem("station4_l4")->addContact(findItem("station4_ab"));
    findItem("station4_ab")->addContact(findItem("station4_l4"));
}

void MainWindow::setupStation5Connections()
{
    // top
    findItem("station5_yst")->addContact(findItem("station5_v2"));
    findItem("station5_v2")->addContact(findItem("station5_yst"));

    findItem("station5_v2")->addContact(findItem("station5_ae2"));
    findItem("station5_ae2")->addContact(findItem("station5_v2"));

    findItem("station5_ae2")->addContact(findItem("station5_h1"));
    findItem("station5_h1")->addContact(findItem("station5_ae2"));

    // left 1
    findItem("station5_h1")->addContact(findItem("station5_yae"));
    findItem("station5_yae")->addContact(findItem("station5_h1"));

    findItem("station5_yae")->addContact(findItem("station5_v1"));
    findItem("station5_v1")->addContact(findItem("station5_yae"));

    findItem("station5_v1")->addContact(findItem("station5_gte"));

    findItem("station5_v1")->addContact(findItem("station5_ae"));
    findItem("station5_ae")->addContact(findItem("station5_v1"));

    findItem("station5_v1")->addContact(findItem("transformer2_l3"));
    findItem("transformer2_l3")->addContact(findItem("station5_v1"));

    // left 2
    findItem("station5_h1")->addContact(findItem("station5_v3"));
    findItem("station5_v3")->addContact(findItem("station5_h1"));

    findItem("station5_v3")->addContact(findItem("station5_ma1"));
    findItem("station5_ma1")->addContact(findItem("station5_v3"));

    findItem("station5_ma1")->addContact(findItem("station5_v4"));
    findItem("station5_v4")->addContact(findItem("station5_ma1"));

    findItem("station5_v4")->addContact(findItem("station5_gtm"));

    findItem("station5_v4")->addContact(findItem("station5_l2"));
    findItem("station5_l2")->addContact(findItem("station5_v4"));

    // left 3
    findItem("station5_h1")->addContact(findItem("station5_v5"));
    findItem("station5_v5")->addContact(findItem("station5_h1"));

    findItem("station5_v5")->addContact(findItem("station5_ya1"));
    findItem("station5_ya1")->addContact(findItem("station5_v5"));

    findItem("station5_ya1")->addContact(findItem("station5_v6"));
    findItem("station5_v6")->addContact(findItem("station5_ya1"));

    findItem("station5_v6")->addContact(findItem("station5_gt1"));

    findItem("station5_v6")->addContact(findItem("station5_l1"));
    findItem("station5_l1")->addContact(findItem("station5_v6"));

    // left 4
    findItem("station5_h1")->addContact(findItem("station5_v7"));
    findItem("station5_v7")->addContact(findItem("station5_h1"));

    findItem("station5_v7")->addContact(findItem("station5_ya2"));
    findItem("station5_ya2")->addContact(findItem("station5_v7"));

    findItem("station5_ya2")->addContact(findItem("station5_v8"));
    findItem("station5_v8")->addContact(findItem("station5_ya2"));

    findItem("station5_v8")->addContact(findItem("station5_gt2"));

    findItem("station5_v8")->addContact(findItem("station5_l3"));
    findItem("station5_l3")->addContact(findItem("station5_v8"));

    // left 5
    findItem("station5_h1")->addContact(findItem("station5_yab"));
    findItem("station5_yab")->addContact(findItem("station5_h1"));

    findItem("station5_yab")->addContact(findItem("station5_v9"));
    findItem("station5_v9")->addContact(findItem("station5_yab"));

    findItem("station5_v9")->addContact(findItem("station5_ab"));
    findItem("station5_ab")->addContact(findItem("station5_v9"));

    findItem("station5_v9")->addContact(findItem("station5_l5"));
    findItem("station5_l5")->addContact(findItem("station5_v9"));

    // bottom
    findItem("station5_ae")->addContact(findItem("station5_l1"));
    findItem("station5_l1")->addContact(findItem("station5_ae"));

    findItem("station5_l1")->addContact(findItem("station5_a1"));
    findItem("station5_a1")->addContact(findItem("station5_l1"));

    findItem("station5_a1")->addContact(findItem("station5_l4"));
    findItem("station5_l4")->addContact(findItem("station5_a1"));

    findItem("station5_l4")->addContact(findItem("station5_ab"));
    findItem("station5_ab")->addContact(findItem("station5_l4"));
}

void MainWindow::setupTransformer1Connections()
{
    // top
    findItem("transformer1_box")->addContact(findItem("transformer1_v8"));
    findItem("transformer1_v8")->addContact(findItem("transformer1_box"));

    findItem("transformer1_v8")->addContact(findItem("transformer1_a"));
    findItem("transformer1_a")->addContact(findItem("transformer1_v8"));

    findItem("transformer1_a")->addContact(findItem("transformer1_h2"));
    findItem("transformer1_h2")->addContact(findItem("transformer1_a"));

    // a1 side
    findItem("transformer1_h2")->addContact(findItem("transformer1_a1"));
    findItem("transformer1_a1")->addContact(findItem("transformer1_h2"));

    findItem("transformer1_a1")->addContact(findItem("transformer1_v7"));
    findItem("transformer1_v7")->addContact(findItem("transformer1_a1"));

    findItem("transformer1_v7")->addContact(findItem("transformer1_k1"));
    findItem("transformer1_k1")->addContact(findItem("transformer1_v7"));

    findItem("transformer1_k1")->addContact(findItem("transformer1_v6"));
    findItem("transformer1_v6")->addContact(findItem("transformer1_k1"));

    findItem("transformer1_v6")->addContact(findItem("transformer1_myst1"));
    findItem("transformer1_myst1")->addContact(findItem("transformer1_v6"));

    findItem("transformer1_myst1")->addContact(findItem("transformer1_v5"));
    findItem("transformer1_v5")->addContact(findItem("transformer1_myst1"));

    findItem("transformer1_v5")->addContact(findItem("transformer1_k10"));
    findItem("transformer1_k10")->addContact(findItem("transformer1_v5"));

    findItem("transformer1_k10")->addContact(findItem("transformer1_v4"));
    findItem("transformer1_v4")->addContact(findItem("transformer1_k10"));

    findItem("transformer1_v4")->addContact(findItem("transformer1_gt10"));

    findItem("transformer1_v4")->addContact(findItem("transformer1_a10"));
    findItem("transformer1_a10")->addContact(findItem("transformer1_v4"));

    findItem("transformer1_a10")->addContact(findItem("transformer1_v3"));
    findItem("transformer1_v3")->addContact(findItem("transformer1_a10"));

    findItem("transformer1_v3")->addContact(findItem("transformer1_ayst1"));
    findItem("transformer1_ayst1")->addContact(findItem("transformer1_v3"));

    findItem("transformer1_ayst1")->addContact(findItem("transformer1_h1"));
    findItem("transformer1_h1")->addContact(findItem("transformer1_ayst1"));

    findItem("transformer1_h1")->addContact(findItem("transformer1_yst1"));
    findItem("transformer1_yst1")->addContact(findItem("transformer1_h1"));

    findItem("transformer1_v3")->addContact(findItem("transformer1_yap"));
    findItem("transformer1_yap")->addContact(findItem("transformer1_v3"));

    findItem("transformer1_v3")->addContact(findItem("transformer1_ke1"));
    findItem("transformer1_ke1")->addContact(findItem("transformer1_v3"));

    findItem("transformer1_ke1")->addContact(findItem("transformer1_v2"));
    findItem("transformer1_v2")->addContact(findItem("transformer1_ke1"));

    findItem("transformer1_v2")->addContact(findItem("transformer1_ae1"));
    findItem("transformer1_ae1")->addContact(findItem("transformer1_v2"));

    findItem("transformer1_ae1")->addContact(findItem("transformer1_v1"));
    findItem("transformer1_v1")->addContact(findItem("transformer1_ae1"));

    findItem("transformer1_v1")->addContact(findItem("transformer1_gte1"));

    findItem("transformer1_v1")->addContact(findItem("transformer1_yan1"));
    findItem("transformer1_yan1")->addContact(findItem("transformer1_v1"));
    findItem("transformer1_yan1")->addContact(findItem("transformer1_l2"));
    findItem("transformer1_l2")->addContact(findItem("transformer1_yan1"));

    findItem("transformer1_v1")->addContact(findItem("transformer1_l1"));
    findItem("transformer1_l1")->addContact(findItem("transformer1_v1"));

    // a2 side
    findItem("transformer1_h2")->addContact(findItem("transformer1_a2"));
    findItem("transformer1_a2")->addContact(findItem("transformer1_h2"));

    findItem("transformer1_a2")->addContact(findItem("transformer1_v9"));
    findItem("transformer1_v9")->addContact(findItem("transformer1_a2"));

    findItem("transformer1_v9")->addContact(findItem("transformer1_k2"));
    findItem("transformer1_k2")->addContact(findItem("transformer1_v9"));

    findItem("transformer1_k2")->addContact(findItem("transformer1_v10"));
    findItem("transformer1_v10")->addContact(findItem("transformer1_k2"));

    findItem("transformer1_v10")->addContact(findItem("transformer1_myst2"));
    findItem("transformer1_myst2")->addContact(findItem("transformer1_v10"));

    findItem("transformer1_myst2")->addContact(findItem("transformer1_v11"));
    findItem("transformer1_v11")->addContact(findItem("transformer1_myst2"));

    findItem("transformer1_v11")->addContact(findItem("transformer1_k20"));
    findItem("transformer1_k20")->addContact(findItem("transformer1_v11"));

    findItem("transformer1_k20")->addContact(findItem("transformer1_v12"));
    findItem("transformer1_v12")->addContact(findItem("transformer1_k20"));

    findItem("transformer1_v12")->addContact(findItem("transformer1_gt20"));

    findItem("transformer1_v12")->addContact(findItem("transformer1_a20"));
    findItem("transformer1_a20")->addContact(findItem("transformer1_v12"));

    findItem("transformer1_a20")->addContact(findItem("transformer1_v13"));
    findItem("transformer1_v13")->addContact(findItem("transformer1_a20"));

    findItem("transformer1_v13")->addContact(findItem("transformer1_ayst2"));
    findItem("transformer1_ayst2")->addContact(findItem("transformer1_v13"));

    findItem("transformer1_ayst2")->addContact(findItem("transformer1_h3"));
    findItem("transformer1_h3")->addContact(findItem("transformer1_ayst2"));

    findItem("transformer1_h3")->addContact(findItem("transformer1_yst2"));
    findItem("transformer1_yst2")->addContact(findItem("transformer1_h3"));

    findItem("transformer1_v13")->addContact(findItem("transformer1_yap"));
    findItem("transformer1_yap")->addContact(findItem("transformer1_v13"));

    findItem("transformer1_v13")->addContact(findItem("transformer1_kb1"));
    findItem("transformer1_kb1")->addContact(findItem("transformer1_v13"));

    findItem("transformer1_kb1")->addContact(findItem("transformer1_v14"));
    findItem("transformer1_v14")->addContact(findItem("transformer1_kb1"));

    findItem("transformer1_v14")->addContact(findItem("transformer1_ab1"));
    findItem("transformer1_ab1")->addContact(findItem("transformer1_v14"));

    findItem("transformer1_ab1")->addContact(findItem("transformer1_v15"));
    findItem("transformer1_v15")->addContact(findItem("transformer1_ab1"));

    findItem("transformer1_v15")->addContact(findItem("transformer1_gtb1"));

    findItem("transformer1_v15")->addContact(findItem("transformer1_yan2"));
    findItem("transformer1_yan2")->addContact(findItem("transformer1_v15"));

    findItem("transformer1_yan2")->addContact(findItem("transformer1_l2"));
    findItem("transformer1_l2")->addContact(findItem("transformer1_yan2"));

    findItem("transformer1_v15")->addContact(findItem("transformer1_l3"));
    findItem("transformer1_l3")->addContact(findItem("transformer1_v15"));
}

void MainWindow::setupTransformer2Connections()
{
    // top
    findItem("transformer2_box")->addContact(findItem("transformer2_v8"));
    findItem("transformer2_v8")->addContact(findItem("transformer2_box"));

    findItem("transformer2_v8")->addContact(findItem("transformer2_a"));
    findItem("transformer2_a")->addContact(findItem("transformer2_v8"));

    findItem("transformer2_a")->addContact(findItem("transformer2_h2"));
    findItem("transformer2_h2")->addContact(findItem("transformer2_a"));

    // a1 side
    findItem("transformer2_h2")->addContact(findItem("transformer2_a1"));
    findItem("transformer2_a1")->addContact(findItem("transformer2_h2"));

    findItem("transformer2_a1")->addContact(findItem("transformer2_v7"));
    findItem("transformer2_v7")->addContact(findItem("transformer2_a1"));

    findItem("transformer2_v7")->addContact(findItem("transformer2_k1"));
    findItem("transformer2_k1")->addContact(findItem("transformer2_v7"));

    findItem("transformer2_k1")->addContact(findItem("transformer2_v6"));
    findItem("transformer2_v6")->addContact(findItem("transformer2_k1"));

    findItem("transformer2_v6")->addContact(findItem("transformer2_myst1"));
    findItem("transformer2_myst1")->addContact(findItem("transformer2_v6"));

    findItem("transformer2_myst1")->addContact(findItem("transformer2_v5"));
    findItem("transformer2_v5")->addContact(findItem("transformer2_myst1"));

    findItem("transformer2_v5")->addContact(findItem("transformer2_k10"));
    findItem("transformer2_k10")->addContact(findItem("transformer2_v5"));

    findItem("transformer2_k10")->addContact(findItem("transformer2_v4"));
    findItem("transformer2_v4")->addContact(findItem("transformer2_k10"));

    findItem("transformer2_v4")->addContact(findItem("transformer2_gt10"));

    findItem("transformer2_v4")->addContact(findItem("transformer2_a10"));
    findItem("transformer2_a10")->addContact(findItem("transformer2_v4"));

    findItem("transformer2_a10")->addContact(findItem("transformer2_v3"));
    findItem("transformer2_v3")->addContact(findItem("transformer2_a10"));

    findItem("transformer2_v3")->addContact(findItem("transformer2_ayst1"));
    findItem("transformer2_ayst1")->addContact(findItem("transformer2_v3"));

    findItem("transformer2_ayst1")->addContact(findItem("transformer2_h1"));
    findItem("transformer2_h1")->addContact(findItem("transformer2_ayst1"));

    findItem("transformer2_h1")->addContact(findItem("transformer2_yst1"));
    findItem("transformer2_yst1")->addContact(findItem("transformer2_h1"));

    findItem("transformer2_v3")->addContact(findItem("transformer2_yap"));
    findItem("transformer2_yap")->addContact(findItem("transformer2_v3"));

    findItem("transformer2_v3")->addContact(findItem("transformer2_ke1"));
    findItem("transformer2_ke1")->addContact(findItem("transformer2_v3"));

    findItem("transformer2_ke1")->addContact(findItem("transformer2_v2"));
    findItem("transformer2_v2")->addContact(findItem("transformer2_ke1"));

    findItem("transformer2_v2")->addContact(findItem("transformer2_ae1"));
    findItem("transformer2_ae1")->addContact(findItem("transformer2_v2"));

    findItem("transformer2_ae1")->addContact(findItem("transformer2_v1"));
    findItem("transformer2_v1")->addContact(findItem("transformer2_ae1"));

    findItem("transformer2_v1")->addContact(findItem("transformer2_gte1"));

    findItem("transformer2_v1")->addContact(findItem("transformer2_yan1"));
    findItem("transformer2_yan1")->addContact(findItem("transformer2_v1"));
    findItem("transformer2_yan1")->addContact(findItem("transformer2_l2"));
    findItem("transformer2_l2")->addContact(findItem("transformer2_yan1"));

    findItem("transformer2_v1")->addContact(findItem("transformer2_l1"));
    findItem("transformer2_l1")->addContact(findItem("transformer2_v1"));

    // a2 side
    findItem("transformer2_h2")->addContact(findItem("transformer2_a2"));
    findItem("transformer2_a2")->addContact(findItem("transformer2_h2"));

    findItem("transformer2_a2")->addContact(findItem("transformer2_v9"));
    findItem("transformer2_v9")->addContact(findItem("transformer2_a2"));

    findItem("transformer2_v9")->addContact(findItem("transformer2_k2"));
    findItem("transformer2_k2")->addContact(findItem("transformer2_v9"));

    findItem("transformer2_k2")->addContact(findItem("transformer2_v10"));
    findItem("transformer2_v10")->addContact(findItem("transformer2_k2"));

    findItem("transformer2_v10")->addContact(findItem("transformer2_myst2"));
    findItem("transformer2_myst2")->addContact(findItem("transformer2_v10"));

    findItem("transformer2_myst2")->addContact(findItem("transformer2_v11"));
    findItem("transformer2_v11")->addContact(findItem("transformer2_myst2"));

    findItem("transformer2_v11")->addContact(findItem("transformer2_k20"));
    findItem("transformer2_k20")->addContact(findItem("transformer2_v11"));

    findItem("transformer2_k20")->addContact(findItem("transformer2_v12"));
    findItem("transformer2_v12")->addContact(findItem("transformer2_k20"));

    findItem("transformer2_v12")->addContact(findItem("transformer2_gt20"));

    findItem("transformer2_v12")->addContact(findItem("transformer2_a20"));
    findItem("transformer2_a20")->addContact(findItem("transformer2_v12"));

    findItem("transformer2_a20")->addContact(findItem("transformer2_v13"));
    findItem("transformer2_v13")->addContact(findItem("transformer2_a20"));

    findItem("transformer2_v13")->addContact(findItem("transformer2_ayst2"));
    findItem("transformer2_ayst2")->addContact(findItem("transformer2_v13"));

    findItem("transformer2_ayst2")->addContact(findItem("transformer2_h3"));
    findItem("transformer2_h3")->addContact(findItem("transformer2_ayst2"));

    findItem("transformer2_h3")->addContact(findItem("transformer2_yst2"));
    findItem("transformer2_yst2")->addContact(findItem("transformer2_h3"));

    findItem("transformer2_v13")->addContact(findItem("transformer2_yap"));
    findItem("transformer2_yap")->addContact(findItem("transformer2_v13"));

    findItem("transformer2_v13")->addContact(findItem("transformer2_kb1"));
    findItem("transformer2_kb1")->addContact(findItem("transformer2_v13"));

    findItem("transformer2_kb1")->addContact(findItem("transformer2_v14"));
    findItem("transformer2_v14")->addContact(findItem("transformer2_kb1"));

    findItem("transformer2_v14")->addContact(findItem("transformer2_ab1"));
    findItem("transformer2_ab1")->addContact(findItem("transformer2_v14"));

    findItem("transformer2_ab1")->addContact(findItem("transformer2_v15"));
    findItem("transformer2_v15")->addContact(findItem("transformer2_ab1"));

    findItem("transformer2_v15")->addContact(findItem("transformer2_gtb1"));

    findItem("transformer2_v15")->addContact(findItem("transformer2_yan2"));
    findItem("transformer2_yan2")->addContact(findItem("transformer2_v15"));

    findItem("transformer2_yan2")->addContact(findItem("transformer2_l2"));
    findItem("transformer2_l2")->addContact(findItem("transformer2_yan2"));

    findItem("transformer2_v15")->addContact(findItem("transformer2_l3"));
    findItem("transformer2_l3")->addContact(findItem("transformer2_v15"));
}

void MainWindow::setupActions()
{
    ui->mainToolBar->hide();

    QMenu* fileMenu = ui->menuBar->addMenu("Dosya");
    QMenu* viewMenu = ui->menuBar->addMenu("Göster");
    QMenu* operationsMenu = ui->menuBar->addMenu("İşlemler");
    QMenu* helpMenu = ui->menuBar->addMenu("Yardım");

    fileMenu->addAction("Çık", qApp, SLOT(quit()));
    helpMenu->addAction("Hakkında", this, SLOT(about()));

    QAction*
    opAction = operations->toggleViewAction();
    opAction->setToolTip("Operasyonlar");
    opAction->setText("Operasyonlar");
    viewMenu->addAction(opAction);

    QAction*
    viewAction = logs->toggleViewAction();
    viewAction->setText("Loglar");
    viewAction->setToolTip("Loglar");
    viewMenu->addAction(viewAction);

    QAction*
    stationsAction = stations->toggleViewAction();
    stationsAction->setText("İstasyonlar");
    stationsAction->setToolTip("İstasyonlar");
    viewMenu->addAction(stationsAction);

    operationsMenu->addAction("Trafo 1 -> Tüm Cihazları Kapat", this, SLOT(on_transformer1CloseAll()));
    operationsMenu->addAction("Trafo 2 -> Tüm Cihazları Kapat", this, SLOT(on_transformer2CloseAll()));
    operationsMenu->addAction("Tüm Cihazları Aç", this, SLOT(on_openAllItems()));
}

void MainWindow::setupSignalsSlots()
{
    foreach (auto gItem, scene->items())
    {
        SvgItem* svgItem = static_cast<SvgItem*>(gItem);

        int svgItemType = svgItem->type();

        if (svgItemType == SvgItem::A ||
                svgItemType == SvgItem::MA ||
                    svgItemType == SvgItem::YA ||
                        svgItemType == SvgItem::K)
        {
            connect(svgItem, &SvgItem::opened, this, [=]{
                QTimer::singleShot(0, operations, &OperationsDockWidget::reload);
            });

            connect(svgItem, &SvgItem::closed, this, [=]{
                QTimer::singleShot(0, operations, &OperationsDockWidget::reload);
            });

            connect(svgItem, &SvgItem::failed, this, [=]{
                QTimer::singleShot(0, operations, &OperationsDockWidget::reload);
            });

            connect(svgItem, &SvgItem::recovered, this, [=]{
                QTimer::singleShot(0, operations, &OperationsDockWidget::reload);
            });


            connect(svgItem, &SvgItem::closed, logs, &LogsDockWidget::on_closed);
            connect(svgItem, &SvgItem::opened, logs, &LogsDockWidget::on_opened);
        }
    }

    // SETUP STATIONS WIDGET SIGNALS
    connect(stations, SIGNAL(buttonClicked(int)), this, SLOT(on_buttonClicked(int)));
    connect(stations, SIGNAL(buttonClicked(int)), operations, SLOT(on_buttonClicked(int)));

    // SETUP OPERATIONS WIDGET SIGNALS
    connect(operations, SIGNAL(itemOpened(QString)), this, SLOT(on_itemOpened(QString)));
    connect(operations, SIGNAL(itemClosed(QString)), this, SLOT(on_itemClosed(QString)));
}

SvgItem *MainWindow::findItem(QString id)
{
    SvgItem* result = nullptr;

    foreach (QGraphicsItem* gItem, scene->items())
    {
        SvgItem* svgItem = dynamic_cast<SvgItem*>(gItem);
        if (svgItem && svgItem->elementId() == id)
        {
            result = svgItem;
        }
    }

    if (!result) {
        qDebug() <<  id << " bulunamadı.";
    }
    return result;
}

void MainWindow::setupDockWidgets()
{
    stations = new StationsDockWidget(this);
    stations->setFeatures(stations->features() & ~QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::DockWidgetArea::TopDockWidgetArea, stations);

    operations = new OperationsDockWidget(this);
    operations->setFeatures(operations->features() & ~QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, operations);

    logs = new LogsDockWidget(this);
    logs->setFeatures(logs->features() & ~QDockWidget::DockWidgetFloatable);
    addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, logs);
}
