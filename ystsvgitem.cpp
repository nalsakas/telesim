#include "ystsvgitem.h"


YSTSvgItem::YSTSvgItem(QDomDocument *document, QSvgRenderer *renderer, QString id, QGraphicsItem *parent)
    : SvgItem(document, renderer, id, parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, false);
}

int YSTSvgItem::type() const
{
    return Type;
}

void YSTSvgItem::powerOn()
{
    if (!hasPower())
    {
        setColor(QColor("red"));
        SvgItem::powerOn();
    }
}

void YSTSvgItem::powerOff()
{
    if (hasPower())
    {
        setColor(QColor("#008000"));
        SvgItem::powerOff();
    }
}
