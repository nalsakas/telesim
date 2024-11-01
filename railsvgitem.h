#ifndef RAILSVGITEM_H
#define RAILSVGITEM_H

#include "svgitem.h"
#include <QtWidgets>
#include <QtSvg>
#include <QtXml>

class RAILSvgItem : public SvgItem
{
    Q_OBJECT
public:
    enum {Type = RAIL};
    RAILSvgItem(QDomDocument* document, QSvgRenderer* renderer, QString id, QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
public:
    int type() const override;

    // SvgItem interface
public slots:
    void powerOn() override;
    void powerOff() override;
};

#endif // RAILSVGITEM_H
