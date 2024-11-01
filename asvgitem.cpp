#include "asvgitem.h"
#include "mainwindow.h"

ASvgItem::ASvgItem(QDomDocument *document, QSvgRenderer *renderer, QString id, QGraphicsItem *parent)
    : SvgItem(document, renderer, id, parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);

    menu = new QMenu(MainWindow::instance);
    closeAction = menu->addAction("Kapat", this, &ASvgItem::close);
    openAction = menu->addAction("Aç", this, &ASvgItem::open);
    failAction = menu->addAction("Arızaya al ", this, &ASvgItem::fail);
    recoverAction = menu->addAction("Arızadan çıkar ", this, &ASvgItem::recover);
}

void ASvgItem::closeNeedle()
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
            children.at(i).toElement().setAttribute("d", "m -2457.7445,-138.04291 0.053,16.05414");
        }
    }
}

int ASvgItem::type() const
{
    return Type;
}

void ASvgItem::powerOn()
{
    if (isClosed())
    {
        SvgItem::powerOn();
    }
}

void ASvgItem::openNeedle()
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
            children.at(i).toElement().setAttribute("d", "m -2458.2429,-138.19045 -7.9812,13.92978");
        }
    }
}

void ASvgItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
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
