#include "mainwindow.h"
#include "UDPCommunicator.h"
#include "CSVBackUp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.resize(550, 400);
    window.show();
    UDPCommunicator comm;
    window.SetUDPCommunicator(comm);
    CSVBackUp csvb;
    window.SetCSVBackUp(csvb);
    return app.exec();
}