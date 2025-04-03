#include "UDPCommunicator.h"
#include "Satellite.h"

#include <QCoreApplication>

#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    std::srand(std::time(nullptr));
    UDPCommunicator comm;
    Satellite s;
    comm.SetSatellite(s);
    return app.exec();
}