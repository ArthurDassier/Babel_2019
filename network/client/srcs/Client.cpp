/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtClient
*/

#include "Client.hpp"

Client::Client(std::string addr, int port, QObject *parent):
    QWidget()
{
    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::LocalHost, 4086);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    QString str = QString::fromUtf8(addr.c_str());
    _add = str;
    _port = port;

    setFixedSize(500, 250);
    _buttonCall = new QPushButton("Call", this);
    // _buttonCall->setFont(QFont("Comic Sans MS", 9));
    _buttonCall->setCursor(Qt::PointingHandCursor);
    _buttonCall->setIcon(QIcon("Green_circle.png"));

    _buttonCommand = new QPushButton("Send to server", this);
    _buttonCommand->setCursor(Qt::PointingHandCursor);

    _labelResponse = new QLabel(QApplication::translate("windowlayout", "Response:"));
    _textResponse = new QLabel(QApplication::translate("windowlayout", "Your answer will appear here"));
    _responseLayout = new QFormLayout;
    _responseLayout->addRow(_labelResponse, _textResponse);

    _labelCommand = new QLabel(QApplication::translate("windowlayout", "Command:"));
    _lineCommand = new QLineEdit();
    _commandLayout = new QFormLayout;
    _commandLayout->addRow(_labelCommand, _lineCommand);

    _labelAddress = new QLabel(QApplication::translate("windowlayout", "Address:"));
    _lineAddress = new QLineEdit();
    _labelPort = new QLabel(QApplication::translate("windowlayout", "Port:"));
    _linePort = new QLineEdit();
    _callLayout = new QFormLayout;
    _callLayout->addRow(_labelAddress, _lineAddress);
    _callLayout->addRow(_labelPort, _linePort);

    _gridLayout = new QGridLayout;
    _gridLayout->addLayout(_responseLayout, 0, 0, 2, 2);
    _gridLayout->addLayout(_commandLayout, 1, 0);
    _gridLayout->addWidget(_buttonCommand, 2, 0);
    _gridLayout->addLayout(_callLayout, 1, 1);
    _gridLayout->addWidget(_buttonCall, 2, 1);

    QObject::connect(_buttonCommand, SIGNAL(clicked()), this, SLOT(SaySomething()));
    QObject::connect(_buttonCall, SIGNAL(clicked()), this, SLOT(tryToCall()));

    this->setLayout(_gridLayout);

    this->setWindowTitle("Babel");
}

void Client::SaySomething()
{
    if (_lineCommand->text() == "")
        return;

    QByteArray Data;
    // QTextStream qtin(stdin);
    QString word = _lineCommand->text();

    // qtin >> word;
    Data = word.toUtf8();
    socket->writeDatagram(Data, _add, _port);
    std::cout << "it's send: " << _lineCommand->text().toStdString() << std::endl;
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
    _textResponse->setText(Buffer.data());
    // std::string str(Buffer.data());
    // std::cout << str << std::endl;
    // if (str[0] == '@')
    //     tryToCall(str);
    // SaySomething();
}

void Client::tryToCall()
{
    if (_lineAddress->text() == "" || _linePort->text() == "")
        return;

    QString qstr = QString::fromUtf8(_lineAddress->text().toStdString().c_str());
    QHostAddress addr(qstr);
    quint16 f_port(std::stoi(_linePort->text().toStdString()));

    QByteArray Data;
    Data.append("Hello from other client\n");
    socket->writeDatagram(Data, addr, f_port);
    //voir si le texte peut apparaitre si trop gros...
}

void Client::takeIp()
{
    std::cout << "adresse ip: " << _lineAddress->text().toStdString() << std::endl;
    std::cout << "port: " << _linePort->text().toStdString() << std::endl;
}