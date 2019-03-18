#include "blockdiagramelement.h"

#include <QGraphicsRectItem>

BlockDiagramElement::BlockDiagramElement()
    : DiagramElement(ToolType::BLOCK)
{
}

void BlockDiagramElement::draw(int posX, int posY, const QSize &size, QGraphicsScene &scene)
{
    auto *shape = new QGraphicsRectItem(posX, posY, size.width(), size.height());
    scene.addItem(shape);
}
