#ifndef LINESVGITEM_H
#define LINESVGITEM_H

#include "svgitem.h"
#include <QtWidgets>
#include <QtSvg>
#include <QtXml>

class LINESvgItem : public SvgItem
{
    Q_OBJECT
public:
    enum {Type = LINE};
    LINESvgItem(QDomDocument* document, QSvgRenderer* renderer, QString id, QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
public:
    int type() const override;

    // SvgItem interface
public slots:
    void powerOn() override;
    void powerOff() override;
};

#endif // LINESVGITEM_H
