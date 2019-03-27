#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <diagramblock.h>

class QGraphicsLineItem;
class QGraphicsSceneMouseEvent;
class QPainterPath;

class Arrow : public QGraphicsLineItem
{
public:
    enum { Type = UserType + 2 };

    Arrow(DiagramBlock *startItem, DiagramBlock *endItem, QGraphicsItem *parent = nullptr);

    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    DiagramBlock *startItem() const { return startBlock; }
    DiagramBlock *endItem() const { return endBlock; }

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    DiagramBlock *startBlock;
    DiagramBlock *endBlock;
    QPolygonF arrowHead;
};

#endif // ARROW_H
