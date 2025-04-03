#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QTimer>
//! 3D Cylinder
#include <Qt3DCore/QEntity>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DExtras/QConeMesh>
#include <Qt3DCore/QTransform>

#include "Data.h"
#include "UDPCommunicator.h"
#include "CSVBackUp.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void AddDataToListWidget(const Data &);
    void SetUDPCommunicator(UDPCommunicator &);
    void SetCSVBackUp(CSVBackUp &);
    //! 3D Cylinder
    void UpdateObjectRotation(float roll, float pitch, float yaw);

private slots:
    void HandleTimerSwitchBtn();
    void OnDataReceived(const Data &);

private:
    QPushButton *timerSwitchBtn;
    QListWidget *dataLst;
    UDPCommunicator *comm;
    CSVBackUp *csvb;
    QLabel *logoImg;
    bool receivingData;
    //! 3D Cylinder
    Qt3DCore::QEntity *rootEntity;
    Qt3DCore::QTransform *transform;
};

#endif