#include "operationsdockwidget.h"
#include "stationsdockwidget.h"
#include "mainwindow.h"
#include "svgitem.h"

OperationsDockWidget::OperationsDockWidget(QWidget *parent) :
    QDockWidget(parent)
{
    model = new QStandardItemModel(this);
    treeView = new QTreeView(this);
    treeView->setModel(model);

    QFontMetrics m(treeView->font());
    QString str(45, 'X');
    treeView->setMinimumWidth(m.horizontalAdvance(str));

    setWidget(treeView);
    setAllowedAreas(Qt::AllDockWidgetAreas);
    connect(model, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(on_itemChanged(QStandardItem*)));
}

OperationsDockWidget::~OperationsDockWidget()
{

}

void OperationsDockWidget::updateModelAll()
{
    updateModelNotr1();
    updateModelStation1();
    updateModelTransformer1();
    updateModelStation2();
    updateModelStation3();
    updateModelNotr2();
    updateModelStation4();
    updateModelTransformer2();
    updateModelStation5();
}

void OperationsDockWidget::updateModelNotr1()
{
    model->setColumnCount(2);

    QStringList labels;
    labels << "İstasyon / Cihaz" << "Kapat";

    model->setHorizontalHeaderLabels(labels);

    QStandardItem*
    parentItem = new QStandardItem("NOTR1");
    parentItem->setEditable(false);

    bool closed = false;
    bool failed = false;

    /* YA1 */
    QStandardItem*
    column1 = new QStandardItem("ya1");
    column1->setEditable(false);

    QStandardItem*
    column2 = new QStandardItem("notr1_ya1");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("notr1_ya1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("notr1_ya1")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* YA2 */
    column1 = new QStandardItem("ya2");
    column1->setEditable(false);

    column2 = new QStandardItem("notr1_ya2");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("notr1_ya2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("notr1_ya2")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* update model and view */
    model->appendRow(parentItem);
    treeView->expandAll();
    treeView->resizeColumnToContents(0);
    treeView->resizeColumnToContents(1);
}

void OperationsDockWidget::updateModelNotr2()
{
    model->setColumnCount(2);

    QStringList labels;
    labels << "İstasyon / Cihaz" << "Kapat";

    model->setHorizontalHeaderLabels(labels);

    QStandardItem*
    parentItem = new QStandardItem("NOTR2");
    parentItem->setEditable(false);

    bool closed = false;
    bool failed = false;

    /* YA1 */
    QStandardItem*
    column1 = new QStandardItem("ya1");
    column1->setEditable(false);

    QStandardItem*
    column2 = new QStandardItem("notr2_ya1");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("notr2_ya1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("notr2_ya1")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* YA2 */
    column1 = new QStandardItem("ya2");
    column1->setEditable(false);
    column2 = new QStandardItem("notr2_ya2");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("notr2_ya2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("notr2_ya2")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* update model and view */
    model->appendRow(parentItem);
    treeView->expandAll();
    treeView->resizeColumnToContents(0);
    treeView->resizeColumnToContents(1);
}

void OperationsDockWidget::updateModelStation1()
{
    model->setColumnCount(2);

    QStringList labels;
    labels << "İstasyon / Cihaz" << "Kapat";

    model->setHorizontalHeaderLabels(labels);

    QStandardItem*
    parentItem = new QStandardItem("İSTASYON 1");
    parentItem->setEditable(false);

    bool closed = false;
    bool failed = false;

    /* ae */
    QStandardItem*
    column1 = new QStandardItem("ae");
    column1->setEditable(false);

    QStandardItem*
    column2 = new QStandardItem("station1_ae");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station1_ae")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station1_ae")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* yae */
    column1 = new QStandardItem("yae");
    column1->setEditable(false);
    column2 = new QStandardItem("station1_yae");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station1_yae")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station1_yae")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ma1 */
    column1 = new QStandardItem("ma1");
    column1->setEditable(false);
    column2 = new QStandardItem("station1_ma1");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station1_ma1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station1_ma1")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* ya1 */
    column1 = new QStandardItem("ya1");
    column1->setEditable(false);
    column2 = new QStandardItem("station1_ya1");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station1_ya1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station1_ya1")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ya2 */
    column1 = new QStandardItem("ya2");
    column1->setEditable(false);
    column2 = new QStandardItem("station1_ya2");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station1_ya2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station1_ya2")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* yab */
    column1 = new QStandardItem("yab");
    column1->setEditable(false);
    column2 = new QStandardItem("station1_yab");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station1_yab")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station1_yab")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ab */
    column1 = new QStandardItem("ab");
    column1->setEditable(false);
    column2 = new QStandardItem("station1_ab");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station1_ab")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station1_ab")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a1 */
    column1 = new QStandardItem("a1");
    column1->setEditable(false);
    column2 = new QStandardItem("station1_a1");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station1_a1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station1_a1")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* update model and view */
    model->appendRow(parentItem);
    treeView->expandAll();
    treeView->resizeColumnToContents(0);
    treeView->resizeColumnToContents(1);
}

void OperationsDockWidget::updateModelStation2()
{
    model->setColumnCount(2);

    QStringList labels;
    labels << "İstasyon / Cihaz" << "Kapat";

    model->setHorizontalHeaderLabels(labels);

    QStandardItem*
    parentItem = new QStandardItem("İSTASYON 2");
    parentItem->setEditable(false);

    bool closed = false;
    bool failed = false;

    /* ae */
    QStandardItem*
    column1 = new QStandardItem("ae");
    column1->setEditable(false);
    QStandardItem*
    column2 = new QStandardItem("station2_ae");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station2_ae")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station2_ae")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* yae */
    column1 = new QStandardItem("yae");
    column1->setEditable(false);
    column2 = new QStandardItem("station2_yae");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station2_yae")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station2_yae")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ma1 */
    column1 = new QStandardItem("ma1");
    column1->setEditable(false);
    column2 = new QStandardItem("station2_ma1");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station2_ma1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station2_ma1")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* ya1 */
    column1 = new QStandardItem("ya1");
    column1->setEditable(false);
    column2 = new QStandardItem("station2_ya1");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station2_ya1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station2_ya1")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ya2 */
    column1 = new QStandardItem("ya2");
    column1->setEditable(false);
    column2 = new QStandardItem("station2_ya2");
    column2->setEditable(true);
    column2->setCheckable(true);

    closed = static_cast<MainWindow*>(parent())->findItem("station2_ya2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);

    failed = static_cast<MainWindow*>(parent())->findItem("station2_ya2")->isFailed();
    column2->setEnabled( failed ? false : true);

    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* yab */
    column1 = new QStandardItem("yab");
    column1->setEditable(false);
    column2 = new QStandardItem("station2_yab");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station2_yab")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station2_yab")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ab */
    column1 = new QStandardItem("ab");
    column1->setEditable(false);
    column2 = new QStandardItem("station2_ab");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station2_ab")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station2_ab")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a1 */
    column1 = new QStandardItem("a1");
    column1->setEditable(false);
    column2 = new QStandardItem("station2_a1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station2_a1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station2_a1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* update model and view */
    model->appendRow(parentItem);
    treeView->expandAll();
    treeView->resizeColumnToContents(0);
    treeView->resizeColumnToContents(1);
}

void OperationsDockWidget::updateModelStation3()
{
    model->setColumnCount(2);

    QStringList labels;
    labels << "İstasyon / Cihaz" << "Kapat";

    model->setHorizontalHeaderLabels(labels);

    QStandardItem*
    parentItem = new QStandardItem("İSTASYON 3");
    parentItem->setEditable(false);

    bool closed = false;
    bool failed = false;

    /* ae */
    QStandardItem*
    column1 = new QStandardItem("ae");
    column1->setEditable(false);
    QStandardItem*
    column2 = new QStandardItem("station3_ae");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station3_ae")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station3_ae")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* yae */
    column1 = new QStandardItem("yae");
    column1->setEditable(false);
    column2 = new QStandardItem("station3_yae");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station3_yae")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station3_yae")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ma1 */
    column1 = new QStandardItem("ma1");
    column1->setEditable(false);
    column2 = new QStandardItem("station3_ma1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station3_ma1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station3_ma1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* ya1 */
    column1 = new QStandardItem("ya1");
    column1->setEditable(false);
    column2 = new QStandardItem("station3_ya1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station3_ya1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station3_ya1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ya2 */
    column1 = new QStandardItem("ya2");
    column1->setEditable(false);
    column2 = new QStandardItem("station3_ya2");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station3_ya2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station3_ya2")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* yab */
    column1 = new QStandardItem("yab");
    column1->setEditable(false);
    column2 = new QStandardItem("station3_yab");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station3_yab")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station3_yab")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ab */
    column1 = new QStandardItem("ab");
    column1->setEditable(false);
    column2 = new QStandardItem("station3_ab");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station3_ab")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station3_ab")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a1 */
    column1 = new QStandardItem("a1");
    column1->setEditable(false);
    column2 = new QStandardItem("station3_a1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station3_a1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station3_a1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* update model and view */
    model->appendRow(parentItem);
    treeView->expandAll();
    treeView->resizeColumnToContents(0);
    treeView->resizeColumnToContents(1);
}

void OperationsDockWidget::updateModelStation4()
{
    model->setColumnCount(2);

    QStringList labels;
    labels << "İstasyon / Cihaz" << "Kapat";

    model->setHorizontalHeaderLabels(labels);

    QStandardItem*
    parentItem = new QStandardItem("İSTASYON 4");
    parentItem->setEditable(false);

    bool closed = false;
    bool failed = false;

    /* ae */
    QStandardItem*
    column1 = new QStandardItem("ae");
    column1->setEditable(false);
    QStandardItem*
    column2 = new QStandardItem("station4_ae");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station4_ae")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station4_ae")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* yae */
    column1 = new QStandardItem("yae");
    column1->setEditable(false);
    column2 = new QStandardItem("station4_yae");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station4_yae")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station4_yae")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ma1 */
    column1 = new QStandardItem("ma1");
    column1->setEditable(false);
    column2 = new QStandardItem("station4_ma1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station4_ma1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station4_ma1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* ya1 */
    column1 = new QStandardItem("ya1");
    column1->setEditable(false);
    column2 = new QStandardItem("station4_ya1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station4_ya1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station4_ya1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ya2 */
    column1 = new QStandardItem("ya2");
    column1->setEditable(false);
    column2 = new QStandardItem("station4_ya2");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station4_ya2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station4_ya2")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* yab */
    column1 = new QStandardItem("yab");
    column1->setEditable(false);
    column2 = new QStandardItem("station4_yab");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station4_yab")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station4_yab")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ab */
    column1 = new QStandardItem("ab");
    column1->setEditable(false);
    column2 = new QStandardItem("station4_ab");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station4_ab")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station4_ab")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a1 */
    column1 = new QStandardItem("a1");
    column1->setEditable(false);
    column2 = new QStandardItem("station4_a1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station4_a1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station4_a1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* update model and view */
    model->appendRow(parentItem);
    treeView->expandAll();
    treeView->resizeColumnToContents(0);
    treeView->resizeColumnToContents(1);
}

void OperationsDockWidget::updateModelStation5()
{
    model->setColumnCount(2);

    QStringList labels;
    labels << "İstasyon / Cihaz" << "Kapat";

    model->setHorizontalHeaderLabels(labels);

    QStandardItem*
    parentItem = new QStandardItem("İSTASYON 5");
    parentItem->setEditable(false);

    bool closed = false;
    bool failed = false;

    /* ae */
    QStandardItem*
    column1 = new QStandardItem("ae");
    column1->setEditable(false);
    QStandardItem*
    column2 = new QStandardItem("station5_ae");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station5_ae")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station5_ae")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* yae */
    column1 = new QStandardItem("yae");
    column1->setEditable(false);
    column2 = new QStandardItem("station5_yae");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station5_yae")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station5_yae")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ma1 */
    column1 = new QStandardItem("ma1");
    column1->setEditable(false);
    column2 = new QStandardItem("station5_ma1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station5_ma1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station5_ma1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* ya1 */
    column1 = new QStandardItem("ya1");
    column1->setEditable(false);
    column2 = new QStandardItem("station5_ya1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station5_ya1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station5_ya1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ya2 */
    column1 = new QStandardItem("ya2");
    column1->setEditable(false);
    column2 = new QStandardItem("station5_ya2");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station5_ya2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station5_ya2")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* yab */
    column1 = new QStandardItem("yab");
    column1->setEditable(false);
    column2 = new QStandardItem("station5_yab");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station5_yab")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station5_yab")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ab */
    column1 = new QStandardItem("ab");
    column1->setEditable(false);
    column2 = new QStandardItem("station5_ab");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station5_ab")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station5_ab")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a1 */
    column1 = new QStandardItem("a1");
    column1->setEditable(false);
    column2 = new QStandardItem("station5_a1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("station5_a1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("station5_a1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);
    /* update model and view */
    model->appendRow(parentItem);
    treeView->expandAll();
    treeView->resizeColumnToContents(0);
    treeView->resizeColumnToContents(1);
}

void OperationsDockWidget::updateModelTransformer1()
{
    model->setColumnCount(2);

    QStringList labels;
    labels << "İstasyon / Cihaz" << "Kapat";

    model->setHorizontalHeaderLabels(labels);

    QStandardItem*
    parentItem = new QStandardItem("TRAFO 1");
    parentItem->setEditable(false);

    bool closed = false;
    bool failed = false;

    /* ae1 */
    QStandardItem*
    column1 = new QStandardItem("ae1");
    column1->setEditable(false);
    QStandardItem*
    column2 = new QStandardItem("transformer1_ae1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_ae1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_ae1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* ke1 */
    column1 = new QStandardItem("ke1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_ke1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_ke1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_ke1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ayst1 */
    column1 = new QStandardItem("ayst1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_ayst1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_ayst1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_ayst1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a10 */
    column1 = new QStandardItem("a10");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_a10");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_a10")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_a10")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* k10 */
    column1 = new QStandardItem("k10");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_k10");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_k10")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_k10")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* k1 */
    column1 = new QStandardItem("k1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_k1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_k1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_k1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a1 */
    column1 = new QStandardItem("a1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_a1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_a1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_a1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a */
    column1 = new QStandardItem("a");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_a");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_a")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_a")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a2 */
    column1 = new QStandardItem("a2");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_a2");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_a2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_a2")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* k2 */
    column1 = new QStandardItem("k2");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_k2");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_k2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_k2")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* k20 */
    column1 = new QStandardItem("k20");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_k20");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_k20")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_k20")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a20 */
    column1 = new QStandardItem("a20");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_a20");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_a20")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_a20")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ayst2 */
    column1 = new QStandardItem("ayst2");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_ayst2");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_ayst2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_ayst2")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* kb1 */
    column1 = new QStandardItem("kb1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_kb1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_kb1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_kb1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ab1 */
    column1 = new QStandardItem("ab1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_ab1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_ab1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_ab1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* yap */
    column1 = new QStandardItem("yap");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_yap");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_yap")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_yap")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* yan1 */
    column1 = new QStandardItem("yan1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_yan1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_yan1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_yan1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* yan2 */
    column1 = new QStandardItem("yan2");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer1_yan2");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer1_yan2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer1_yan2")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* update model and view */
    model->appendRow(parentItem);
    treeView->expandAll();
    treeView->resizeColumnToContents(0);
    treeView->resizeColumnToContents(1);
}

void OperationsDockWidget::updateModelTransformer2()
{
    model->setColumnCount(2);

    QStringList labels;
    labels << "İstasyon / Cihaz" << "Kapat";

    model->setHorizontalHeaderLabels(labels);

    QStandardItem*
    parentItem = new QStandardItem("TRAFO 2");
    parentItem->setEditable(false);

    bool closed = false;
    bool failed = false;

    /* ae1 */
    QStandardItem*
    column1 = new QStandardItem("ae1");
    column1->setEditable(false);
    QStandardItem*
    column2 = new QStandardItem("transformer2_ae1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_ae1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_ae1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);


    /* ke1 */
    column1 = new QStandardItem("ke1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_ke1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_ke1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_ke1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ayst1 */
    column1 = new QStandardItem("ayst1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_ayst1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_ayst1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_ayst1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a10 */
    column1 = new QStandardItem("a10");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_a10");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_a10")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_a10")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* k10 */
    column1 = new QStandardItem("k10");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_k10");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_k10")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_k10")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* k1 */
    column1 = new QStandardItem("k1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_k1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_k1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_k1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a1 */
    column1 = new QStandardItem("a1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_a1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_a1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_a1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a */
    column1 = new QStandardItem("a");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_a");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_a")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_a")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a2 */
    column1 = new QStandardItem("a2");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_a2");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_a2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_a2")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* k2 */
    column1 = new QStandardItem("k2");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_k2");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_k2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_k2")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* k20 */
    column1 = new QStandardItem("k20");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_k20");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_k20")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_k20")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* a20 */
    column1 = new QStandardItem("a20");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_a20");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_a20")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_a20")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ayst2 */
    column1 = new QStandardItem("ayst2");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_ayst2");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_ayst2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_ayst2")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* kb1 */
    column1 = new QStandardItem("kb1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_kb1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_kb1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_kb1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* ab1 */
    column1 = new QStandardItem("ab1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_ab1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_ab1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_ab1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* yap */
    column1 = new QStandardItem("yap");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_yap");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_yap")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_yap")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* yan1 */
    column1 = new QStandardItem("yan1");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_yan1");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_yan1")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_yan1")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* yan2 */
    column1 = new QStandardItem("yan2");
    column1->setEditable(false);
    column2 = new QStandardItem("transformer2_yan2");
    column2->setEditable(true);
    column2->setCheckable(true);
    closed = static_cast<MainWindow*>(parent())->findItem("transformer2_yan2")->isClosed();
    column2->setCheckState( closed ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    failed = static_cast<MainWindow*>(parent())->findItem("transformer2_yan2")->isFailed();
    column2->setEnabled( failed ? false : true);
    parentItem->appendRow(QList<QStandardItem*>() << column1 << column2);

    /* update model and view */
    model->appendRow(parentItem);
    treeView->expandAll();
    treeView->resizeColumnToContents(0);
    treeView->resizeColumnToContents(1);
}

void OperationsDockWidget::on_buttonClicked(int id)
{
    buttonState = id;

    switch (id) {
    case StationsDockWidget::ALL:
        model->clear();
        updateModelAll();
        break;
    case StationsDockWidget::NOTR1:
        model->clear();
        updateModelNotr1();
        break;
    case StationsDockWidget::NOTR2:
        model->clear();
        updateModelNotr2();
        break;
    case StationsDockWidget::STATION1:
        model->clear();
        updateModelStation1();
        break;
    case StationsDockWidget::STATION2:
        model->clear();
        updateModelStation2();
        break;
    case StationsDockWidget::STATION3:
        model->clear();
        updateModelStation3();
        break;
    case StationsDockWidget::STATION4:
        model->clear();
        updateModelStation4();
        break;
    case StationsDockWidget::STATION5:
        model->clear();
        updateModelStation5();
        break;
    case StationsDockWidget::TRANSFORMER1:
        model->clear();
        updateModelTransformer1();
        break;
    case StationsDockWidget::TRANSFORMER2:
        model->clear();
        updateModelTransformer2();
        break;
    }
}

void OperationsDockWidget::reload()
{
    on_buttonClicked(buttonState);
}

void OperationsDockWidget::on_itemChanged(QStandardItem *item)
{
    if(item->checkState() == Qt::Checked)
    {
        emit itemClosed(item->text());
    }
    else if(item->checkState() == Qt::Unchecked)
    {
        emit itemOpened(item->text());
    }
}
