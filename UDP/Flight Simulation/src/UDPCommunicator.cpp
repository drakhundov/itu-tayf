#include <UDPCommunicator.h>

#include "Data.h"

#include <cstdlib>
#include <iostream>
UDPCommunicator::UDPCommunicator()
{
    udpSocket.bind(std::atoi(std::getenv("FS_PORT")));
    GS_PORT = std::atoi(std::getenv("GS_PORT"));
    connect(&udpSocket, &QUdpSocket::readyRead, this, &UDPCommunicator::CheckStatus);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &UDPCommunicator::OnTimeout);
}

void UDPCommunicator::OnTimeout()
{
    Data data{(std::rand() % 2) * 0.1f, (std::rand() % 4) * 0.1f, (std::rand() % 2) * 0.1f};
    SendData(data);
}

void UDPCommunicator::SendData(const Data &data)
{
    QByteArray datagram;
    QDataStream stream(&datagram, QIODevice::WriteOnly);
    stream << data.height << data.temp << data.pressure;
    udpSocket.writeDatagram(datagram, QHostAddress::LocalHost, GS_PORT);
}

void UDPCommunicator::CheckStatus()
{
    while (udpSocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
        bool startSending;
        QDataStream stream(datagram);
        stream >> startSending;
        if (startSending)
        {
            timer->start(1000);
        }
        else
        {
            timer->stop();
        }
    }
}