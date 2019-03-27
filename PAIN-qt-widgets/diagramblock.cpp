#include "diagramblock.h"
#include "arrow.h"
#include <QGraphicsScene>
#include <QTextDocument>
#include <QGraphicsSceneContextMenuEvent>
#include <QDebug>

constexpr qreal DiagramBlock::DEFAULT_WIDTH;
constexpr qreal DiagramBlock::DEFAULT_HEIGHT;
constexpr qreal DiagramBlock::MAX_WIDTH;
constexpr qreal DiagramBlock::MAX_HEIGHT;

DiagramBlock::DiagramBlock(const QString &text, QGraphicsScene &scene, const QPointF &scenePos, QGraphicsItem *parent)
    : QObject(), QGraphicsRectItem(parent), text(new QGraphicsTextItem(text, this)), contextMenu(std::make_unique<QMenu>(tr("contMen")))
{
    //qDebug() << "DiagramBlock:textWidth - " << this->text->textWidth(); // -1
    auto width = std::max(DEFAULT_WIDTH, this->text->boundingRect().width());
    if (width > MAX_WIDTH) {
        width = MAX_WIDTH;
        //this->text->setTextWidth(MAX_WIDTH);
    }
    auto height = std::max(DEFAULT_HEIGHT, this->text->boundingRect().height());
    if (height > MAX_HEIGHT) {
        height = MAX_HEIGHT;
        //TODO text document's (editor's) height
    }

    this->text->setTabChangesFocus(true);

    auto localX = 0.0 - width/2.0;
    auto localY = 0.0 - height/2.0;
    setRect(localX, localY, width, height);

    this->text->setTextWidth(width);
    auto textCenter = this->text->boundingRect().center();
    this->text->setPos(-textCenter);

    setBrush(Qt::white);
    setFlags(ItemIsMovable | ItemIsSelectable | ItemClipsChildrenToShape | ItemSendsGeometryChanges);
    setPos(scenePos);
    scene.addItem(this);

    QObject::connect(this->text->document(), &QTextDocument::contentsChanged, this, &DiagramBlock::textContentsChanged);

    contextMenu->addAction(tr("Bring to Front"));
    contextMenu->addAction(tr("Send to Back"));
    contextMenu->addSeparator();
    contextMenu->addAction(tr("Scale x2"), [this]{ setScale(2.0); });
    contextMenu->addSeparator();
    contextMenu->addAction(tr("Delete"), this, &DiagramBlock::removedFromScene);
}

void DiagramBlock::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    this->text->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->text->setFocus();
}

QVariant DiagramBlock::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemSelectedHasChanged && !isSelected()) {
        this->text->setTextInteractionFlags(Qt::NoTextInteraction);
        return QVariant{};
    }
    else if (change == ItemPositionChange) {
        for (auto arrow : arrows) {
            arrow->updatePosition();
        }
    }

    return QGraphicsItem::itemChange(change, value);
}

void DiagramBlock::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    if (!isSelected()) {
        scene()->clearSelection();
        setSelected(true);
    }
    contextMenu->popup(event->screenPos());
}

void DiagramBlock::textContentsChanged()
{
    auto newTextCenter = this->text->boundingRect().center();
    this->text->setPos(-newTextCenter);
}

void DiagramBlock::removedFromScene()
{
    removeArrows();
    scene()->removeItem(this);
    // The ownership of item is passed on to the caller (i.e., QGraphicsScene will no longer delete item when destroyed)
    QObject::deleteLater();
    //delete this;
}

void DiagramBlock::removeArrow(Arrow *arrow)
{
    int index = arrows.indexOf(arrow);

    if (index != -1)
        arrows.removeAt(index);
}

void DiagramBlock::removeArrows()
{
    for (auto arrow : arrows) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void DiagramBlock::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}
