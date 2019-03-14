#ifndef CANVASSCENE_H
#define CANVASSCENE_H

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

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

private:
    // canvas state machine
    State canvasState = State::DRAW_PENCIL;        //State::POINTER;
    bool mouseLeftPressedDown = false;
};

#endif // CANVASSCENE_H
