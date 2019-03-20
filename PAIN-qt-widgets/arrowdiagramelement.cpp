#include "arrowdiagramelement.h"
#include <QGraphicsScene>

ArrowDiagramElement::ArrowDiagramElement(QGraphicsScene &scene)
    //: DiagramElement(ToolType::ARROW)
    : scene(scene)
{
}

void ArrowDiagramElement::draw(const QPoint &point1, const QPoint &point2)
{
    this->point1 = point1;
    this->point2 = point2;
    setLine({point1, point2});

    if (!addedToScene) {
        scene.addItem(this);
        addedToScene = true;
    }
}

void ArrowDiagramElement::scaleRedraw(const QPoint &point2)
{
    this->point2 = point2;
    setLine({this->point1, point2});        // QLineF(QLine) + QLine(QPoint, QPoint)
    //setLine(QLineF{this->point1, point2});  // QLineF(QPointF, QPointF) + QPointF(QPoint)
}

void ArrowDiagramElement::processMousePress(const QPoint &point)
{
    draw(point, point);
}

void ArrowDiagramElement::processMouseDrag(const QPoint &startPoint, const QPoint &currPoint, bool dragFinished)
{
    scaleRedraw(currPoint);
}
