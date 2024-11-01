#include "railsvgitem.h"


RAILSvgItem::RAILSvgItem(QDomDocument *document, QSvgRenderer *renderer, QString id, QGraphicsItem *parent)
    : SvgItem(document, renderer, id, parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, false);
}

int RAILSvgItem::type() const
{
    return Type;
}

void RAILSvgItem::powerOn()
{
    if (!hasPower())
    {
        setColor(QColor("red"));
        SvgItem::powerOn();
    }
}

void RAILSvgItem::powerOff()
{
    if (hasPower())
    {
        setColor(QColor("#008000"));
        SvgItem::powerOff();
    }
}
