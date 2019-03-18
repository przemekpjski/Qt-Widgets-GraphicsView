#ifndef BLOCKDIAGRAMELEMENT_H
#define BLOCKDIAGRAMELEMENT_H

#include "diagramelement.h"

class BlockDiagramElement : public DiagramElement
{
public:
    BlockDiagramElement();
    ~BlockDiagramElement() override = default;

    void draw(int posX, int posY, const QSize &size, QGraphicsScene &scene) override;
};

#endif // BLOCKDIAGRAMELEMENT_H
