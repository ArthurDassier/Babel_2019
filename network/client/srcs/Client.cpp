/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtClient
*/

#include "Client.hpp"

Client::Client(std::string addr, int port, QObject *parent):
    QObject(parent)
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 4086);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    QString str = QString::fromUtf8(addr.c_str());
    _add = str;
    _port = port;
}

void Client::SaySomething()
{
    QByteArray Data;
    QTextStream qtin(stdin);
    QString word;

    qtin >> word;
    Data = word.toUtf8();
    socket->writeDatagram(Data, _add, _port);
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
    std::string str(Buffer.data());
    std::cout << str << std::endl;
    if (str[0] == '@')
        tryToCall(str);
    SaySomething();
}

void Client::tryToCall(std::string str)
{
    str.erase(str.begin());
    std::cout << "Voici qui je dois call: " << str << std::endl;

    std::string addresse = str.substr(0, str.find(':'));
    std::string port = str.substr(str.find(':') + 1);
    QString qstr = QString::fromUtf8(addresse.c_str());
    QHostAddress addr(qstr);
    quint16 f_port(std::stoi(port));
    std::cout << "port : " << str.substr(str.find(':')) << std::endl;

    QByteArray Data;
    Data.append("Hello from UDP");
    socket->writeDatagram(Data, addr, f_port);
}