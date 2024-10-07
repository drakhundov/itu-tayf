#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QTimer>

#include "Data.h"
#include "UDPCommunicator.h"
#include "CSVBackUp.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void AddDataToListWidget(const Data &);
    void SetUDPCommunicator(UDPCommunicator &);
    void SetCSVBackUp(CSVBackUp &);

private slots:
    void HandleTimerSwitchBtn();
    void OnDataReceived(const Data &);

private:
    QPushButton *timerSwitchBtn;
    QListWidget *dataLst;
    UDPCommunicator *comm;
    CSVBackUp *csvb;
    bool receivingData;
};

#endif