#ifndef UDPC
#define UDPC

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QHostAddress>
#include <QDataStream>

#include "Satellite.h"

class UDPCommunicator : public QObject
{
public:
    UDPCommunicator();
    void SetSatellite(Satellite &);

private slots:
    void CheckStatus();
    void OnTimeout();

private:
    QUdpSocket udpSocket;
    QTimer *timer;
    QHostAddress gsAddress;
    void SendData(const Data &);
    int GS_PORT;
    Satellite *satellite;
};

#endif