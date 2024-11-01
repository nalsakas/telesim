#include "linesvgitem.h"


LINESvgItem::LINESvgItem(QDomDocument *document, QSvgRenderer *renderer, QString id, QGraphicsItem *parent)
    : SvgItem(document, renderer, id, parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, false);
}

int LINESvgItem::type() const
{
    return Type;
}

void LINESvgItem::powerOn()
{
    if (!hasPower())
    {
        setColor(QColor("red"));
        SvgItem::powerOn();
    }
}

void LINESvgItem::powerOff()
{
    if (hasPower())
    {
        setColor(QColor("#008000"));
        SvgItem::powerOff();
    }
}
