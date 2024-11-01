#include "textsvgitem.h"


TEXTSvgItem::TEXTSvgItem(QDomDocument *document, QSvgRenderer *renderer, QString id, QGraphicsItem *parent)
    : SvgItem(document, renderer, id, parent)
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, false);
}

int TEXTSvgItem::type() const
{
    return Type;
}

void TEXTSvgItem::powerOn()
{
    if (!hasPower())
    {
        setColor(QColor("red"));
        SvgItem::powerOn();
    }
}

void TEXTSvgItem::powerOff()
{
    if (hasPower())
    {
        setColor(QColor("#008000"));
        SvgItem::powerOff();
    }
}
