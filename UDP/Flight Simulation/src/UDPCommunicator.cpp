#include "UDPCommunicator.h"

#include <cstdlib>

UDPCommunicator::UDPCommunicator()
{
    udpSocket.bind(std::atoi(std::getenv("FS_PORT")));
    GS_PORT = std::atoi(std::getenv("GS_PORT"));
    connect(&udpSocket, &QUdpSocket::readyRead, this, &UDPCommunicator::CheckStatus);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &UDPCommunicator::OnTimeout);
}

void UDPCommunicator::SetSatellite(Satellite &satelliteRef) { satellite = &satelliteRef; }

void UDPCommunicator::OnTimeout()
{
    satellite->UpdateData();
    SendData(satellite->GetData());
}

void UDPCommunicator::SendData(const Data &data)
{
    QByteArray datagram;
    QDataStream stream(&datagram, QIODevice::WriteOnly);
    stream << data.height << data.temp << data.pressure << data.pitch << data.yaw << data.roll;
    qint64 bytesWritten = udpSocket.writeDatagram(datagram, QHostAddress::LocalHost, GS_PORT);
    if (bytesWritten == -1)
    {
        qCritical() << "Failed to write datagram:" << udpSocket.errorString();
    }
}

void UDPCommunicator::CheckStatus()
{
    while (udpSocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());
        bool startSending;
        QDataStream stream(&datagram, QIODevice::ReadOnly);
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