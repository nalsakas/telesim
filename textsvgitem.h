#ifndef TEXTSVGITEM_H
#define TEXTSVGITEM_H

#include "svgitem.h"
#include <QtWidgets>
#include <QtSvg>
#include <QtXml>

class TEXTSvgItem : public SvgItem
{
    Q_OBJECT
public:
    enum {Type = TEXT};
    TEXTSvgItem(QDomDocument* document, QSvgRenderer* renderer, QString id, QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
public:
    int type() const override;

    // SvgItem interface
public slots:
    void powerOn() override;
    void powerOff() override;
};

#endif // TEXTSVGITEM_H
