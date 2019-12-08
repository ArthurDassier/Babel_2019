/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtClient
*/

#include "Client.hpp"

Client::Client(std::string addr, int port, QObject *parent):
    _add(addr),
    _port(port),
    QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 4086);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void Client::SaySomething()
{
    QByteArray Data;
    QTextStream qtin(stdin); 
    QString word;
    QString str = QString::fromUtf8(_add.c_str());
    QHostAddress addr(str);

    qtin >> word;
    Data = word.toUtf8();
    quint16 port(_port);
    socket->writeDatagram(Data, addr, port);
}

void Client::readyRead()
{
    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(Buffer.data(), Buffer.size(), &sender, &senderPort);

    // qDebug() << "Message from: " << sender.toString();
    // qDebug() << "Message port: " << senderPort;
    // qDebug() << "Message: " << Buffer;
    std::string test(Buffer.data());
    std::cout << test;
    SaySomething();
}