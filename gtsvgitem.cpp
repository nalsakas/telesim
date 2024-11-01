#include "gtsvgitem.h"


GTSvgItem::GTSvgItem(QDomDocument *document, QSvgRenderer *renderer, QString id, QGraphicsItem *parent)
    : SvgItem(document, renderer, id, parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, false);
}

int GTSvgItem::type() const
{
    return Type;
}

void GTSvgItem::powerOn()
{
    if (!hasPower())
    {
        setColor(QColor("red"));
        SvgItem::powerOn();
    }
}

void GTSvgItem::powerOff()
{
    if (hasPower())
    {
        setColor(QColor("#008000"));
        SvgItem::powerOff();
    }
}
