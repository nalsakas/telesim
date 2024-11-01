#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QtWidgets>

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = nullptr);

    // QWidget interface
protected:
    void wheelEvent(QWheelEvent *event) override;
};

#endif // GRAPHICSVIEW_H
