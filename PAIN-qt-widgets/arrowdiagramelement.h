#ifndef ARROWDIAGRAMELEMENT_H
#define ARROWDIAGRAMELEMENT_H

#include "diagramelement.h"

class ArrowDiagramElement : public DiagramElement
{
public:
    ArrowDiagramElement();

    void draw(int posX, int posY, const QSize &size, QGraphicsScene &scene) override
    {}
};

#endif // ARROWDIAGRAMELEMENT_H
