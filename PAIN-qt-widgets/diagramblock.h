#ifndef DIAGRAMBLOCK_H
#define DIAGRAMBLOCK_H

#include <QGraphicsRectItem>
#include <QObject>
#include <memory>
#include <QMenu>
#include <QList>

class Arrow;

class DiagramBlock : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    enum { Type = UserType + 1 };
    static constexpr qreal DEFAULT_WIDTH = 100.0;
    static constexpr qreal MAX_WIDTH = 200.0;
    static constexpr qreal DEFAULT_HEIGHT = 100.0;
    static constexpr qreal MAX_HEIGHT = 200.0;

public:
    explicit DiagramBlock(const QString &text, QGraphicsScene &scene, const QPointF &scenePos = {0, 0}, QGraphicsItem *parent = nullptr);

    void removeArrow(Arrow *arrow);
    void removeArrows();
    void addArrow(Arrow *arrow);
    int type() const override { return Type; }

public slots:
    void textContentsChanged();

protected slots:
    void removedFromScene();

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;

private:
    QGraphicsTextItem *text;
    std::unique_ptr<QMenu> contextMenu;
    QList<Arrow *> arrows;
};

#endif // DIAGRAMBLOCK_H
