#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "canvasscene.h"

//#include <QtWidgets>
#include <QMainWindow>

class QGraphicsView;
class QGraphicsScene;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void initGraphicsScene();

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    CanvasScene *scene;
};

#endif // MAINWINDOW_H
