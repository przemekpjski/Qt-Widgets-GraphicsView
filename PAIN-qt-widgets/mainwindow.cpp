#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    view = ui->graphicsView;

    // connect signals to slots
    /*QObject::*///connect(ui->resetSliderButton, &QPushButton::clicked, ui->horizontalSlider, &QSlider::setValue);
    // works because false -> 0 ??
    connect(ui->resetSliderButton, &QPushButton::clicked, /*ui->horizontalSlider,*/ [this]{ ui->horizontalSlider->setValue(0); });
    // but, is it ok?
    // (threads of execution, objects being destroyed, ... - see: https://doc.qt.io/qt-5/signalsandslots.html#signals-and-slots-with-default-arguments
    // C++11 lambda expressions are effectively inline slots

    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));

    /*
    auto zeroCentralWidgetMargin = [this]{
        auto margins = ui->centralWidget->layout()->contentsMargins();
        margins.setRight(0);
        ui->centralWidget->layout()->setContentsMargins(margins);
    };
    */
    // then restore the margin, when dock location was changed
    //   and also when widget was set floating
    // so: store previous dock area (?) - another class for managing this margin operations?

    initGraphicsScene();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initGraphicsScene()
{
    //scene = new QGraphicsScene(0, 0, 400, 400, this);
    scene = new CanvasScene(this);
    scene->setSceneRect(QRectF(0, 0, 400, 400));
    // test
    scene->addRect(QRectF(20, 20, 200, 300), QPen(Qt::blue), QBrush(Qt::yellow));

    auto sceneCoordsPoint = view->mapToScene(100, 100);
    auto viewportCoordsPoint = view->mapFromScene(50, 50);
    qDebug("View coords (100,100) in scene coords: (%d,%d).",
           static_cast<int>(sceneCoordsPoint.x()),
           static_cast<int>(sceneCoordsPoint.y()));
    qDebug("Scene coords (50,50) in viewport coords: (%d,%d).",
           static_cast<int>(viewportCoordsPoint.x()),
           static_cast<int>(viewportCoordsPoint.y()));

    view->setScene(scene);
    //? ui->graphicsView->show();
}
