#ifndef DIAGRAMELEMENT_H
#define DIAGRAMELEMENT_H

#include "tooltype.h"
#include <QSize>
#include <QGraphicsScene>
#include <memory>

class DiagramElement
{
public:
    /*enum class Type {
        BLOCK,
        ARROW
    };*/

public:
    DiagramElement(ToolType elementType) : elementType(elementType) {}
    virtual ~DiagramElement() = 0;

    virtual void draw(int posX, int posY, const QSize &size, QGraphicsScene &scene) = 0;

protected:
    //std::unique_ptr<DiagramElement> subelements;
    ToolType elementType;
};

#endif // DIAGRAMELEMENT_H
