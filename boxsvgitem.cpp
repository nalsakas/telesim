#include "boxsvgitem.h"
#include "mainwindow.h"

BOXSvgItem::BOXSvgItem(QDomDocument *document, QSvgRenderer *renderer, QString id, QGraphicsItem *parent)
    : SvgItem(document, renderer, id, parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, false);

    menu = new QMenu(MainWindow::instance);
    closeAction = menu->addAction("Şebeke Enerji Ver", this, &BOXSvgItem::forceClose);
    openAction = menu->addAction("Şebeke Enerji Kes", this, &BOXSvgItem::forceOpen);
    failAction = menu->addAction("Arızaya al ", this, &BOXSvgItem::fail);
    recoverAction = menu->addAction("Arızadan çıkar ", this, &BOXSvgItem::recover);
}

int BOXSvgItem::type() const
{
    return Type;
}

void BOXSvgItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    isClosed() || isFailed() ? closeAction->setEnabled(false) : closeAction->setEnabled(true);
    isOpened() || isFailed()? openAction->setEnabled(false) : openAction->setEnabled(true);
    isFailed() ? failAction->setEnabled(false) : failAction->setEnabled(true);
    isRecovered() ? recoverAction->setEnabled(false) : recoverAction->setEnabled(true);

    menu->addAction(closeAction);
    menu->addAction(openAction);
    menu->addSeparator();
    menu->addAction(failAction);
    menu->addAction(recoverAction);
    menu->popup(QCursor::pos());

    event->accept();
}

void BOXSvgItem::powerOn()
{
    if (isClosed())
    {
        SvgItem::powerOn();
    }
}

void BOXSvgItem::forceClose()
{
    setClosed(true);

    QTimer::singleShot(0, this, [=]{
        QProgressBar bar;
        bar.setRange(0,0);
        bar.setMaximumHeight(MainWindow::instance->statusBar()->height() - 10);
        MainWindow::instance->statusBar()->addWidget(&bar);

        powerOn();

        MainWindow::instance->statusBar()->removeWidget(&bar);
    });

    emit closed();
}

void BOXSvgItem::setDomElementColor(QDomElement element, QColor color)
{

    element.setAttribute("stroke", color.name());
    element.setAttribute("fill", color.name());

    for (int i = 0; i < element.childNodes().count(); i++)
    {
        auto children = element.childNodes().at(i).toElement();
        setDomElementColor(children, color);
    }

}
