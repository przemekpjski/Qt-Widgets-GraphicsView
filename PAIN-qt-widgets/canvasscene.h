#ifndef CANVASSCENE_H
#define CANVASSCENE_H

#include "tool.h"
#include <QGraphicsScene>

class CanvasScene : public QGraphicsScene
{
    /*Q_OBJECT ? */
public:
    enum class State {  //Mode?
        POINTER,
        DRAW_PENCIL,    //BRUSH?
        DRAW_RECTANGLE
    };

    CanvasScene(QObject *parent);

    State state() const noexcept { return canvasState; }

public slots:
    void setState(State state) noexcept { canvasState = state; }
    void setTool(int type) noexcept { setTool(ToolType(type)); }
    void setTool(ToolType toolType) noexcept { selectedTool = Tool(toolType); }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

    void drawUsingTool(qreal x, qreal y);

private:
    // canvas state machine
    State canvasState = State::POINTER;
    bool mouseLeftPressedDown = false;

    Tool selectedTool = ToolType::NO_TOOL;
    QSize drawSize = QSize(50, 50);

    QGraphicsItem *itemBeingDrawn;
};

#endif // CANVASSCENE_H
