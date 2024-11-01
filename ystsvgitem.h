#ifndef YSTSVGITEM_H
#define YSTSVGITEM_H

#include "svgitem.h"
#include <QtWidgets>
#include <QtSvg>
#include <QtXml>

class YSTSvgItem : public SvgItem
{
    Q_OBJECT
public:
    enum {Type = YST};
    YSTSvgItem(QDomDocument* document, QSvgRenderer* renderer, QString id, QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
public:
    int type() const override;

    // SvgItem interface
public slots:
    void powerOn() override;
    void powerOff() override;
};

#endif // YSTSVGITEM_H
