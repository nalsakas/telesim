#include "masvgitem.h"
#include "mainwindow.h"

MASvgItem::MASvgItem(QDomDocument *document, QSvgRenderer *renderer, QString id, QGraphicsItem *parent)
    : SvgItem(document, renderer, id, parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);

    menu = new QMenu(MainWindow::instance);
    closeAction = menu->addAction("Kapat", this, &MASvgItem::close);
    openAction = menu->addAction("Aç", this, &MASvgItem::open);
    failAction = menu->addAction("Arızaya al ", this, &MASvgItem::fail);
    recoverAction = menu->addAction("Arızadan çıkar ", this, &MASvgItem::recover);
}

void MASvgItem::closeNeedle()
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
            children.at(i).toElement().setAttribute("d", "m -2638.8615,439.25426 -0.122,-16.0542");
        }
    }
}

int MASvgItem::type() const
{
    return Type;
}

void MASvgItem::powerOn()
{
    if (isClosed())
    {
        SvgItem::powerOn();
    }
}

void MASvgItem::openNeedle()
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
            children.at(i).toElement().setAttribute("d", "m -2638.158,439.44185 7.9214,-13.96437");
        }
    }
}

void MASvgItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
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
