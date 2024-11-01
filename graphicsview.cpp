#include "graphicsview.h"

GraphicsView::GraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    setDragMode(DragMode::ScrollHandDrag);
}

void GraphicsView::wheelEvent(QWheelEvent *event)
{
    event->accept();

    setTransformationAnchor(QGraphicsView::ViewportAnchor::NoAnchor);
    QPointF oldPos = mapToScene(event->pos());

    double zoomInFactor = 1.25;
    double zoomOutFactor = 1.0 / 1.25;

    if (event->angleDelta().y() > 0 )
    {
        scale(zoomInFactor, zoomInFactor);
    }
    else
    {
       scale(zoomOutFactor, zoomOutFactor);
    }

    QPointF newPos = mapToScene(event->pos());

    QPointF diff = newPos - oldPos;

    translate(diff.x(), diff.y());
}
