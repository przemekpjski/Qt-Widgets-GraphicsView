#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "scene.h"

//#include <QtWidgets>
#include <QMainWindow>

class QGraphicsView;
class QActionGroup;

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
    Scene *scene;
    QActionGroup *toolActionGroup;
};

#endif // MAINWINDOW_H
