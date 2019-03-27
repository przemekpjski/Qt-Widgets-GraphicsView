#include "scene.h"
#include "diagramblock.h"
#include "arrow.h"

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QtMath>
#include <QtDebug>

#include <cassert>

//TODO solve app crashes

//[DONE] hide mousePosLabel when mouse is outside of the QGraphicsView
//TODO move mousePosLabel to the top
//TODO wheelEvent -> zoom
//TODO arrows keyboardEvent -> scroll scene (move view over scene)
//TODO contextMenuEvent (rightButton click)

constexpr QPointF Scene::mouseOutsidePos;

Scene::Scene()
    : mousePosLabel(new Label),
      selectRect(new QGraphicsRectItem)
{
    mousePosLabel->hide();
    selectRect->hide();

    mousePosLabel->setZValue(100);
    selectRect->setBrush({QColor(255, 0, 255, 128), Qt::FDiagPattern});
    selectRect->setPen(Qt::NoPen);

    addItem(mousePosLabel);
    addItem(selectRect);

    installEventFilter(this);
}

void Scene::setTool(PointerMode tool)
{
    pointerMode = tool;
    qDebug() << "Tool selected: " << static_cast<int>(pointerMode);
}

//TODO lazy init of Label (singleton?)
//@callSuper
void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);

    // const auto& / auto&& ?
    auto pos = event->scenePos();
    this->mousePos = pos;

    //Note that the returned value is always Qt::NoButton for mouse move events.

    if (pointerMode == PointerMode::DRAW_ARROW && arrowDragLine != nullptr) {
        QLineF newLine(arrowDragLine->line().p1(), event->scenePos());
        arrowDragLine->setLine(newLine);
    }
    else if (pointerMode == PointerMode::DRAW_SELECTION_RECT && mouseBtnDown == Qt::LeftButton) {
        auto rectX = std::min(selectStartPos.x(), pos.x());
        auto rectY = std::min(selectStartPos.y(), pos.y());
        selectRect->setRect({
            rectX, rectY,
            qFabs(pos.x() - selectStartPos.x()),
            qFabs(pos.y() - selectStartPos.y())
        });
    }
    //TODO if item dragged => do not draw selectRect and do not setSelectionArea on mousebtn release

    //if (event->modifiers().testFlag(Qt::ControlModifier))
    if (mousePosLabel->isVisible())
    {
        updateMousePosLabel();  //TODO as part of MousePosLabel class (its responsibility)
        // setVisible(bool) ?
    }
}

//@callSuper
void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    mouseBtnDown = event->button();
    if (mouseBtnDown != Qt::LeftButton)
        return;

    if (pointerMode == PointerMode::INSERT_BLOCK)
        return;
    else if (pointerMode == PointerMode::DRAW_ARROW)
    {
        qDebug() << "Draw Arrow MousePress";
        arrowDragLine = new QGraphicsLineItem(QLineF(event->scenePos(), event->scenePos()));
        arrowDragLine->setPen(QPen(Qt::black, 2));
        addItem(arrowDragLine);
        return;
    }

    if (selectedItems().empty())
    {
        pointerMode = PointerMode::DRAW_SELECTION_RECT;

        selectStartPos = event->scenePos();
        selectRect->setRect({selectStartPos, selectStartPos});
        selectRect->show();
    }
    else
        pointerMode = PointerMode::ITEM_SELECTED;

    qDebug() << "Items selected ctn in mousePress: " << selectedItems().size();
    QGraphicsScene::mousePressEvent(event);
}

//@callSuper
void Scene::mouseReleaseEvent([[maybe_unused]] QGraphicsSceneMouseEvent *event)
{
    //QGraphicsScene::mouseReleaseEvent(event);
    if (pointerMode == PointerMode::INSERT_BLOCK)
    {
        new DiagramBlock("Hello, Diagram Block", *this, event->scenePos());
    }
    else if (pointerMode == PointerMode::DRAW_ARROW && arrowDragLine != nullptr)
    {
        qDebug() << "Draw Arrpw MouseRelease";
        tryInsertArrow();
    }
    else if (pointerMode == PointerMode::DRAW_SELECTION_RECT)
    {
        setSelectionArea(selectRect->shape());
        selectRect->hide();
        selectRect->setRect({});
    }

    mouseBtnDown = Qt::NoButton;
    //qDebug() << "releaseEvent.button() == " << event->button();   // the button that was pressed previous to this call

    QGraphicsScene::mouseReleaseEvent(event);

    //if (!selectedItems().empty())
    //    pointerMode = PointerMode::ITEM_SELECTED;
}

//@callSuper
void Scene::keyPressEvent(QKeyEvent *event)
{
    QGraphicsScene::keyPressEvent(event);

    if (event->key() == Qt::Key_Control && mousePos != mouseOutsidePos)
    {
        updateMousePosLabel();
        mousePosLabel->show();
        qDebug() << "mousePosLabel shown";
    }
}

//@callSuper
void Scene::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsScene::keyReleaseEvent(event);

    if (event->key() == Qt::Key_Control)
    {
        mousePosLabel->hide();
        qDebug() << "mousePosLabel hidden";
    }
}

//@callSuper
bool Scene::event(QEvent *event)
{
    return QGraphicsScene::event(event);
}

bool Scene::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Leave)
    {
        qDebug() << "Mouse left the scene";
        mousePos = mouseOutsidePos;
        mousePosLabel->hide();
        //? return true;
    }

    return QGraphicsScene::eventFilter(watched, event);
    //return false;
}

//@callSuper
void Scene::focusOutEvent(QFocusEvent *event)
{
    QGraphicsScene::focusOutEvent(event);

    //mousePosLabel->hide();
}

void Scene::updateMousePosLabel() const noexcept
{
    //mousePosLabel->hide();
    mousePosLabel->setPos(mousePos.x() + 5.0, mousePos.y() - mousePosLabel->rect().height() - 5.0);
    mousePosLabel->setText(
        "x:" + QString::number(mousePos.x()) + ", y:" + QString::number(mousePos.y())
    );
    //mousePosLabel->show();
}

void Scene::tryInsertArrow()
{
    QList<QGraphicsItem *> startItems = items(arrowDragLine->line().p1());
    if (!startItems.empty() && startItems.first() == arrowDragLine)
        startItems.removeFirst();
    if (!startItems.empty() && startItems.first()->type() == QGraphicsTextItem::Type)
        startItems.removeFirst();
    QList<QGraphicsItem *> endItems = items(arrowDragLine->line().p2());
    if (!endItems.empty() && endItems.first() == arrowDragLine)
        endItems.removeFirst();
    if (!endItems.empty() && endItems.first()->type() == QGraphicsTextItem::Type)
        endItems.removeFirst();

    removeItem(arrowDragLine);
    delete arrowDragLine;

    if (!startItems.empty() && !endItems.empty()) {
        auto firstStartItem = startItems.first();
        auto firstEndItem = endItems.first();
        if (firstStartItem->type() == DiagramBlock::Type &&
                firstEndItem->type() == DiagramBlock::Type &&
                firstStartItem != firstEndItem) {
            DiagramBlock *startItem = qgraphicsitem_cast<DiagramBlock *>(firstStartItem);
            DiagramBlock *endItem = qgraphicsitem_cast<DiagramBlock *>(firstEndItem);

            Arrow *arrow = new Arrow(startItem, endItem);
            startItem->addArrow(arrow);
            endItem->addArrow(arrow);
            arrow->setZValue(-100.0);
            addItem(arrow);
            // The arrow must be updated to adjust its start and end points to the items
            arrow->updatePosition();
        }
    }
    arrowDragLine = nullptr;
}
