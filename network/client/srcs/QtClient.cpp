/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtClient
*/

#include "QtClient.hpp"

// Client::Client(QObject *parent):
//     QObject(parent)
// {
//     socket = new QUdpSocket(this);
//     socket->bind(QHostAddress::LocalHost, 1234);
//     connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
// }

// void Client::SayHello()
// {
//     QByteArray Data;
//     Data.append("Hello from UDP Land");
//     QHostAddress addr("10.41.167.130");
//     socket->writeDatagram(Data, addr, 7000);
// }

// void Client::readyRead()
// {
//     QByteArray Buffer;
//     Buffer.resize(socket->pendingDatagramSize());

//     QHostAddress sender;
//     quint16 senderPort;
//     socket->readDatagram(Buffer.data(), Buffer.size(), &sender, &senderPort);

//     qDebug() << "Message from: " << sender.toString();
//     qDebug() << "Message port: " << senderPort;
//     qDebug() << "Message: " << Buffer;
// }

MyTcpSocket::MyTcpSocket(QObject *parent) : QObject(parent)
{
}

void MyTcpSocket::doConnect()
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    qDebug() << "connecting...";

    // this is not blocking call
    socket->connectToHost("10.41.167.130", 4242);

    // we need to wait...
    if (!socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << socket->errorString();
    }
}

void MyTcpSocket::connected()
{
    qDebug() << "connected...";

    // Hey server, tell me about you.
    socket->write("HEAD / HTTP/1.0\r\n\r\n\r\n\r\n");
}

void MyTcpSocket::disconnected()
{
    qDebug() << "disconnected...";
}

void MyTcpSocket::bytesWritten(qint64 bytes)
{
    qDebug() << bytes << " bytes written...";
}

void MyTcpSocket::readyRead()
{
    qDebug() << "reading...";

    // read the data from the socket
    qDebug() << socket->readAll();
}