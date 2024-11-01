#ifndef BOXSVGITEM_H
#define BOXSVGITEM_H

#include "svgitem.h"
#include <QtWidgets>
#include <QtSvg>
#include <QtXml>

class BOXSvgItem : public SvgItem
{
    Q_OBJECT
public:
    enum {Type = BOX};
    BOXSvgItem(QDomDocument* document, QSvgRenderer* renderer, QString id, QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
public:
    int type() const override; 

    // QGraphicsItem interface
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    // SvgItem interface
public slots:
    void powerOn() override;
    void forceClose() override;

    // SvgItem interface
protected:
    void setDomElementColor(QDomElement element, QColor color) override;

private:
    QMenu *menu;
    QAction* closeAction;
    QAction* openAction;
    QAction* failAction;
    QAction* recoverAction;
};

#endif // BOXSVGITEM_H
