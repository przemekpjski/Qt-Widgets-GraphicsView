#ifndef ARROWDIAGRAMELEMENT_H
#define ARROWDIAGRAMELEMENT_H

//#include "diagramelement.h"
#include <QGraphicsLineItem>

//#include <QGraphicsScene>
class QGraphicsScene;

class ArrowDiagramElement : public QGraphicsLineItem
{
public:
    explicit ArrowDiagramElement(QGraphicsScene &scene);

    //void setScene(
    void draw(const QPoint &point1, const QPoint &point2 /*, QGraphicsScene &scene*/);
    void scaleRedraw(const QPoint &point2);

    void processMousePress(const QPoint &point);
    void processMouseDrag(const QPoint &startPoint, const QPoint &currPoint, bool dragFinished = false);
    void processMouseRelease(const QPoint &point);

protected:
    QPoint point1, point2;
    QGraphicsScene &scene;
    mutable bool addedToScene = false;
};

#endif // ARROWDIAGRAMELEMENT_H
