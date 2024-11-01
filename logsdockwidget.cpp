#include "logsdockwidget.h"
#include "svgitem.h"

LogsDockWidget::LogsDockWidget(QWidget *parent) :
    QDockWidget(parent)
{
    tableWidget = new QTableWidget(this);
    tableWidget->setRowCount(0);
    tableWidget->setColumnCount(2);
    tableWidget->verticalHeader()->setVisible(false);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Tarih / Saat" << "Mesaj");
    tableWidget->setShowGrid(false);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    QFontMetrics m(tableWidget->font());
    QString str(45, 'X');
    tableWidget->setMinimumWidth(m.horizontalAdvance(str));

    setWidget(tableWidget);
    setAllowedAreas(Qt::AllDockWidgetAreas);
}

LogsDockWidget::~LogsDockWidget()
{

}

void LogsDockWidget::on_closed()
{
    tableWidget->insertRow(tableWidget->rowCount());

    QTableWidgetItem*
    item = new QTableWidgetItem(QDateTime::currentDateTime().toString(Qt::DateFormat::LocalDate));
    item->setTextAlignment(Qt::AlignLeft);
    tableWidget->setItem(tableWidget->rowCount() - 1, 0, item);

    SvgItem* senderObj = static_cast<SvgItem*>(sender());

    QString message = "Cihaz " + senderObj->elementId() + " kapatıldı.";

    item = new QTableWidgetItem(message);
    item->setTextAlignment(Qt::AlignLeft);
    tableWidget->setItem(tableWidget->rowCount() - 1, 1, item);

    tableWidget->scrollToBottom();
    tableWidget->resizeColumnsToContents();
    tableWidget->resizeRowsToContents();
}

void LogsDockWidget::on_opened()
{
    tableWidget->insertRow(tableWidget->rowCount());

    QTableWidgetItem*
    item = new QTableWidgetItem(QDateTime::currentDateTime().toString(Qt::DateFormat::LocalDate));
    item->setTextAlignment(Qt::AlignLeft);
    tableWidget->setItem(tableWidget->rowCount() - 1, 0, item);

    SvgItem* senderObj = static_cast<SvgItem*>(sender());

    QString message = "Cihaz " + senderObj->elementId() + " açıldı.";

    item = new QTableWidgetItem(message);
    item->setTextAlignment(Qt::AlignLeft);
    tableWidget->setItem(tableWidget->rowCount() - 1, 1, item);

    tableWidget->scrollToBottom();
    tableWidget->resizeColumnsToContents();
    tableWidget->resizeRowsToContents();
}
