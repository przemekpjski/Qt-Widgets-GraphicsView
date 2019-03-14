#include "canvasscene.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QMessageBox>

CanvasScene::CanvasScene(QObject *parent)
    : QGraphicsScene(parent)
{
}

void CanvasScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    mouseLeftPressedDown = true;

    auto scenePos = mouseEvent->scenePos();
    QGraphicsItem *item;
    if ((item = itemAt(scenePos, QTransform{})) != nullptr)
        qDebug("Clicked item's type: %d.", item->type());

    //QString coordsMessage()
    //QMessageBox::about(parent(), tr("Click scene coordinates"),
    //                   tr(""))
    qDebug("Click scene coords: (%d,%d).",
           static_cast<int>(scenePos.x()),
           static_cast<int>(scenePos.y()));

    // relay to the base implementation to propagate the event to an QGraphicsItem if any
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void CanvasScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    //void(mouseEvent*);
    //TODO? check if Qt::LeftButton
    mouseLeftPressedDown = false;
}

void CanvasScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseLeftPressedDown) {
        auto mousePos = mouseEvent->scenePos();

        switch (canvasState) {
        case State::DRAW_PENCIL:
            //TODO dispatch Pencil class
            //2 - pencil size
            //TODO - mousePos as center of the ellipse
            addEllipse(QRectF(mousePos.x(), mousePos.y(), 2, 2), Qt::NoPen, Qt::black);
            break;
        default:
            ;
        }
    }
}


