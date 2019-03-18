#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QtDebug>
#include "mainwindow_utils.h"
#include "tooltype.h"

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
    initDiagramTools();
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

void MainWindow::initDiagramTools()
{
    std::array< std::pair<QString, int>, 4> tools = {
        std::make_pair("Block", ToolType::BLOCK),
        {"Group", ToolType::DIAGRAM_BLOCK},
        {"Arrow", ToolType::ARROW},
        {"Label", ToolType::LABEL},
    };

    toolButtonGroup = new QButtonGroup(this);
    //toolButtonGroup->setExclusive(false);
    connect(toolButtonGroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
            scene, static_cast<void (CanvasScene::*)(int)>(&CanvasScene::setTool));
            //this, SLOT(toolSelected(int))

    QWidget *toolWidget = new QWidget;
    QGridLayout *toolLayout = new QGridLayout;

    int row = 0, column = 0;
    for (auto&& tool : tools) {
        toolLayout->addWidget(mainwindow_utils::createToolButton(
                                  QIcon(":/icons/icons/new-512.png"), tool.first, *toolButtonGroup, tool.second),
                              row, column++);
        if (column == 2) {
            ++row;
            column = 0;
        }
    }

    toolWidget->setLayout(toolLayout);
    int pageIndex = ui->toolBox->addItem(toolWidget, tr("Test"));
    //whatis? ui->toolBox->setItemEnabled(pageIndex, true);
    ui->toolBox->setCurrentIndex(pageIndex);
}

void MainWindow::toolSelected(int toolType)
{
    qDebug("Tool Selected, type: %d", toolType);
}
