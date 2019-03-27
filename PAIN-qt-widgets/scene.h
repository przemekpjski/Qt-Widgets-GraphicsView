#ifndef SCENE_H
#define SCENE_H

#include "label.h"
#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
public:
    //TODO (C++11) using base_class_ctors (delegation)
    Scene();

public:
    enum class PointerMode : unsigned char {
        POINTER = 0,
        POINTER_WITH_POSLABEL,
        DRAW_SELECTION_RECT,
        ITEM_SELECTED,
        INSERT_BLOCK,
        DRAW_ARROW,
    };

public slots:
    void setTool(PointerMode tool);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    bool event(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void tryInsertArrow();

    void focusOutEvent(QFocusEvent *event) override;

private:
    inline void updateMousePosLabel() const noexcept;

protected:
    //TODO something different. (wrong decision)
    static constexpr QPointF mouseOutsidePos = {-1.0, -1.0};
    //private mutable bool mouseLeftScene = true;
    // + eventFilter QEvent::Enter ?

private:
    Label *mousePosLabel;

    mutable QPointF selectStartPos;
    mutable QGraphicsRectItem *selectRect;
    mutable QGraphicsLineItem *arrowDragLine = nullptr;

    //mutable Qt::MouseButtons mouseBtnsDown;   // flag
    mutable Qt::MouseButton mouseBtnDown = Qt::NoButton;
    mutable QPointF mousePos = mouseOutsidePos;
    mutable PointerMode pointerMode = PointerMode::POINTER;
};

#endif // SCENE_H
