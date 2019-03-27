#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow), toolActionGroup(new QActionGroup(this))
{
    ui->setupUi(this);
    view = ui->graphicsView;

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    toolActionGroup->addAction(ui->actionPointer);
    toolActionGroup->addAction(ui->actionBlock);
    toolActionGroup->addAction(ui->actionArrow);
    ui->actionPointer->setChecked(true);

    initGraphicsScene();

    //TODO connect slots
    connect(ui->actionPointer, &QAction::toggled, [this](bool checked){ if (checked) scene->setTool(Scene::PointerMode::POINTER); });
    connect(ui->actionBlock, &QAction::toggled, [this](bool checked){ if (checked) scene->setTool(Scene::PointerMode::INSERT_BLOCK); });
    connect(ui->actionArrow, &QAction::toggled, [this](bool checked){ if (checked) scene->setTool(Scene::PointerMode::DRAW_ARROW); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGraphicsScene()
{
    scene = new Scene;
    scene->setSceneRect(QRectF(0, 0, 1000, 1000));
    view->setScene(scene);
}
