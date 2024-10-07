#ifndef UDPC_H
#define UDPC_H

#include <QObject>
#include <QUdpSocket>

#include "Data.h"

class UDPCommunicator : public QObject
{
    Q_OBJECT

public:
    UDPCommunicator();
    void StartListening();
    void StopListening();

signals:
    void DataReceived(const Data &);

private slots:
    void ProcessPendingDatagrams();

private:
    QUdpSocket udpSocket;
    void SetStatus(bool);
    int FS_PORT;
};

#endif