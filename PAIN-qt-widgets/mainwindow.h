#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "canvasscene.h"

//#include <QtWidgets>
#include <QMainWindow>
#include <QButtonGroup>

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
    void initDiagramTools();

private slots:
    void toolSelected(int toolType);

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    CanvasScene *scene;

    QButtonGroup *toolButtonGroup;
};

#endif // MAINWINDOW_H
