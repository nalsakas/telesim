#include "ksvgitem.h"
#include "mainwindow.h"

KSvgItem::KSvgItem(QDomDocument *document, QSvgRenderer *renderer, QString id, QGraphicsItem *parent)
    : SvgItem(document, renderer, id, parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);

    menu = new QMenu(MainWindow::instance);
    closeAction = menu->addAction("Kapat", this, &KSvgItem::close);
    openAction = menu->addAction("Aç", this, &KSvgItem::open);
    failAction = menu->addAction("Arızaya al ", this, &KSvgItem::fail);
    recoverAction = menu->addAction("Arızadan çıkar ", this, &KSvgItem::recover);
}

void KSvgItem::closeNeedle()
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
            children.at(i).toElement().setAttribute("d", "m 2813.8015,1981.3322 0.01,28.9953");
        }
    }
}

int KSvgItem::type() const
{
    return Type;
}

void KSvgItem::powerOn()
{
    if (isClosed())
    {
        SvgItem::powerOn();
    }
}

void KSvgItem::openNeedle()
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
            children.at(i).toElement().setAttribute("d", "m 2813.6856,1981.1357 -7.5046,28.0073");
        }
    }
}

void KSvgItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
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
