#include "UDPCommunicator.h"

#include <QDataStream>
#include <QHostAddress>
#include <cstdlib>

#include "Data.h"

UDPCommunicator::UDPCommunicator()
{
    udpSocket.bind(std::atoi(std::getenv("GS_PORT")));
    FS_PORT = std::atoi(std::getenv("FS_PORT"));
}

void UDPCommunicator::StartListening()
{
    connect(&udpSocket, &QUdpSocket::readyRead, this, &UDPCommunicator::ProcessPendingDatagrams);
    SetStatus(true);
}

void UDPCommunicator::StopListening()
{
    disconnect(&udpSocket, &QUdpSocket::readyRead, this, &UDPCommunicator::ProcessPendingDatagrams);
    SetStatus(false);
}

void UDPCommunicator::ProcessPendingDatagrams()
{
    while (udpSocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
        Data data;
        QDataStream stream(&datagram, QIODevice::ReadOnly);
        stream >> data.height >> data.temp >> data.pressure;
        emit DataReceived(data);
    }
}

void UDPCommunicator::SetStatus(bool status)
{
    // true - start sending
    // false - don't
    QByteArray datagram;
    QDataStream stream(&datagram, QIODevice::WriteOnly);
    stream << status;
    udpSocket.writeDatagram(datagram, QHostAddress::LocalHost, FS_PORT);
}