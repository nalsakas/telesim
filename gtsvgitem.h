#ifndef GTSVGITEM_H
#define GTSVGITEM_H

#include "svgitem.h"
#include <QtWidgets>
#include <QtSvg>
#include <QtXml>

class GTSvgItem : public SvgItem
{
    Q_OBJECT
public:
    enum {Type = GT};
    GTSvgItem(QDomDocument* document, QSvgRenderer* renderer, QString id, QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
public:
    int type() const override;

    // SvgItem interface
public slots:
    void powerOn() override;
    void powerOff() override;
};

#endif // GTSVGITEM_H
