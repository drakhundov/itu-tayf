#include "mainwindow.h"
#include "button_styling.h"

#include <QPixmap>
#include <QDebug>
#include <sstream>

//! 3D Cylinder
#include <Qt3DExtras/QCylinderMesh>
#include <Qt3DRender/QCamera>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //! 3D Cylinder
    rootEntity = new Qt3DCore::QEntity();
    transform = new Qt3DCore::QTransform();

    // Set up the 3D scene
    Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow();
    QWidget *container = QWidget::createWindowContainer(view);
    container->setMinimumSize(QSize(800, 600));
    container->setMaximumSize(QSize(800, 600));
    container->setFocusPolicy(Qt::TabFocus);

    // Create a camera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(0, 0, 20.0f));
    camera->setViewCenter(QVector3D(0, 0, 0));

    // Create a camera controller
    Qt3DExtras::QOrbitCameraController *camController = new Qt3DExtras::QOrbitCameraController(rootEntity);
    camController->setLinearSpeed(50.0f);
    camController->setLookSpeed(180.0f);
    camController->setCamera(camera);

    // Create a 3D object (Cylinder)
    Qt3DCore::QEntity *CylinderEntity = new Qt3DCore::QEntity(rootEntity);
    Qt3DExtras::QCylinderMesh *cylMesh = new Qt3DExtras::QCylinderMesh();
    cylMesh->setRadius(1.0f);
    // cylMesh->setTopRadius(0.0f);
    // cylMesh->setBottomRadius(1.0f);
    cylMesh->setLength(3.0f);
    cylMesh->setRings(50);
    cylMesh->setSlices(20);

    Qt3DExtras::QPhongMaterial *material = new Qt3DExtras::QPhongMaterial();
    material->setDiffuse(QColor(QRgb(0x928327)));

    CylinderEntity->addComponent(cylMesh);
    CylinderEntity->addComponent(material);
    CylinderEntity->addComponent(transform);

    view->setRootEntity(rootEntity);

    QWidget *viewContainer = QWidget::createWindowContainer(view);
    viewContainer->setFixedSize(500, 300);
    viewContainer->move(100, 100);

    // Create a layout and add widgets
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(timerSwitchBtn);
    layout->addWidget(dataLst);
    layout->addWidget(logoImg);
    layout->addWidget(container);

    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    //! UI
    this->setStyleSheet("border: 1px solid black;");

    receivingData = false;
    timerSwitchBtn = new QPushButton("START", this);
    timerSwitchBtn->resize(100, 30);
    timerSwitchBtn->move(100, 50);
    connect(timerSwitchBtn, &QPushButton::clicked, this,
            [this]()
            {
                receivingData = !receivingData;
                HandleTimerSwitchBtn();
                if (comm)
                {
                    if (receivingData)
                    {
                        comm->StartListening();
                        connect(comm, &UDPCommunicator::DataReceived, this, &MainWindow::OnDataReceived);
                        if (csvb)
                        {
                            connect(comm, &UDPCommunicator::DataReceived, csvb, &CSVBackUp::BackUpData);
                        }
                    }
                    else
                    {
                        comm->StopListening();
                        disconnect(comm, &UDPCommunicator::DataReceived, this, &MainWindow::OnDataReceived);
                        if (csvb)
                        {
                            disconnect(comm, &UDPCommunicator::DataReceived, csvb, &CSVBackUp::BackUpData);
                        }
                    }
                }
            });
    UpdBtnStyle(timerSwitchBtn, "color", "white");
    UpdBtnStyle(timerSwitchBtn, "background-color", ButtonStyles::START_BG);

    dataLst = new QListWidget(this);
    dataLst->move(50, 100);
    dataLst->resize(200, 150);

    logoImg = new QLabel(this);
    QPixmap pm(":/assets/logo.png");
    pm = pm.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    if (pm.isNull())
    {
        qDebug() << "Failed to load image.";
    }
    else
    {
        logoImg->setPixmap(pm);
        logoImg->move(100, 275);
        logoImg->resize(pm.size());
        logoImg->show();
        logoImg->setStyleSheet("border: none;");
        qDebug() << "Image loaded successfully.";
    }
}

void MainWindow::SetUDPCommunicator(UDPCommunicator &commRef) { comm = &commRef; }
void MainWindow::SetCSVBackUp(CSVBackUp &csvbRef) { csvb = &csvbRef; }

void MainWindow::HandleTimerSwitchBtn()
{
    if (receivingData)
    {
        timerSwitchBtn->setText("STOP");
        UpdBtnStyle(timerSwitchBtn, "background-color", ButtonStyles::STOP_BG);
    }
    else
    {
        timerSwitchBtn->setText("START");
        UpdBtnStyle(timerSwitchBtn, "background-color", ButtonStyles::START_BG);
    }
}

void MainWindow::OnDataReceived(const Data &data)
{
    AddDataToListWidget(data);
    UpdateObjectRotation(data.pitch, data.yaw, data.roll);
}

void MainWindow::AddDataToListWidget(const Data &d)
{
    std::ostringstream oss;
    oss << "h: " << d.height << "m, t: " << d.temp << "C, p: " << d.pressure << "hPa";
    dataLst->addItem(QString::fromStdString(oss.str()));
}

void MainWindow::UpdateObjectRotation(float pitch, float yaw, float roll)
{
    transform->setRotation(QQuaternion::fromEulerAngles(pitch, yaw, roll));
}

MainWindow::~MainWindow() {}