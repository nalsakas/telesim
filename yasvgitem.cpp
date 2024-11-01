#include "yasvgitem.h"
#include "mainwindow.h"

YASvgItem::YASvgItem(QDomDocument *document, QSvgRenderer *renderer, QString id, QGraphicsItem *parent)
    : SvgItem(document, renderer, id, parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);

    menu = new QMenu(MainWindow::instance);
    closeAction = menu->addAction("Kapat", this, &YASvgItem::close);
    openAction = menu->addAction("Aç", this, &YASvgItem::open);
    failAction = menu->addAction("Arızaya al ", this, &YASvgItem::fail);
    recoverAction = menu->addAction("Arızadan çıkar ", this, &YASvgItem::recover);
}

void YASvgItem::closeNeedle()
{
    QDomElement element = findDomElementById(document()->documentElement(), elementId());
    if (element.isNull())
    {
        qDebug() << QString("Can't find elementid = %1  in DOM tree.").arg(elementId());
        return;
    }

    auto children = element.childNodes();
    for (int i = 0; i < children.count(); i++)
    {
        if (children.at(i).toElement().attribute("class") == "needle")
        {
            children.at(i).toElement().setAttribute("d", "m 227.34788,1759.925 -28.9917,0.1281");
        }
    }
}

int YASvgItem::type() const
{
    return Type;
}

void YASvgItem::powerOn()
{
    if (isClosed())
    {
        SvgItem::powerOn();
    }
}

void YASvgItem::openNeedle()
{
    QDomElement element = findDomElementById(document()->documentElement(), elementId());
    if (element.isNull())
    {
        qDebug() << QString("Can't find elementid = %1  in DOM tree.").arg(elementId());
        return;
    }

    auto children = element.childNodes();
    for (int i = 0; i < children.count(); i++)
    {
        if (children.at(i).toElement().attribute("class") == "needle")
        {
            children.at(i).toElement().setAttribute("d", "m 227.93098,1759.6402 -28.0073,-7.5045");
        }
    }
}

void YASvgItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
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
    menu->popup(event->screenPos());

    event->accept();
}
