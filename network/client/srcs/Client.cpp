/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtClient
*/

#include "Client.hpp"

Client::Client(QObject *parent):
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
    QHostAddress addr("127.0.0.1");

    qtin >> word;
    Data = word.toUtf8();
    socket->writeDatagram(Data, addr, 8080);
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