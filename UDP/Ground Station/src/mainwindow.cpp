#include "mainwindow.h"
#include "button_styling.h"

#include <sstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
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
}

void MainWindow::SetUDPCommunicator(UDPCommunicator &commRef) { comm = &commRef; }
void MainWindow::SetCSVBackUp(CSVBackUp &csvbRef) { csvb = &csvbRef; }

void MainWindow::OnDataReceived(const Data &data) { AddDataToListWidget(data); }

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

void MainWindow::AddDataToListWidget(const Data &d)
{
    std::ostringstream oss;
    oss << "h: " << d.height << "m, t: " << d.temp << "C, p: " << d.pressure << "hPa";
    dataLst->addItem(QString::fromStdString(oss.str()));
}

MainWindow::~MainWindow() {}