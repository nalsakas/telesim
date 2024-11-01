#ifndef MASVGITEM_H
#define MASVGITEM_H

#include "svgitem.h"
#include <QtWidgets>
#include <QtSvg>
#include <QtXml>

class MASvgItem : public SvgItem
{
    Q_OBJECT
public:
    enum {Type = MA};
    MASvgItem(QDomDocument* document, QSvgRenderer* renderer, QString id, QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

    // SvgItem interface
protected:
    void openNeedle() override;
    void closeNeedle() override;

    // QGraphicsItem interface
public:
    int type() const override;

    // SvgItem interface
public slots:
    void powerOn() override;

private:
    QMenu *menu;
    QAction* closeAction;
    QAction* openAction;
    QAction* failAction;
    QAction* recoverAction;
};

#endif // MASVGITEM_H
