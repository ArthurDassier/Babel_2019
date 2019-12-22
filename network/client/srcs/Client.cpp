/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtClient
*/

#include "Client.hpp"

Client::Client(std::string addr, int port, QObject *parent):
    QWidget(),
    _isCalling(false),
    _firstTime(true),
    _timerSpeak(new QTimer()),
    UI(this)
{
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    QString str = QString::fromUtf8(addr.c_str());
    _add = str;
    _port = port;

    _timerSpeak->setInterval(1);
    
    setFixedSize(500, 250);
    setLayout(UI.renderInterface());
    setWindowTitle("Babel");

    connect(UI.getCommandButton(), SIGNAL(clicked()), this, SLOT(sendToServer()));
    connect(UI.getCallButton(), SIGNAL(clicked()), this, SLOT(initCall()));
    connect(_timerSpeak, SIGNAL(timeout()), this, SLOT(speaking()));
}

void Client::sendToServer()
{
    if (UI.getCommand()->text() == "")
        return;

    QByteArray Data;
    QString word = UI.getCommand()->text();

    Data = word.toUtf8();
    socket->writeDatagram(Data, _add, _port);
    std::cout << "it's send: " << UI.getCommand()->text().toStdString() << std::endl;
}

void Client::readyRead()
{
    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 senderPort;
    socket->readDatagram(Buffer.data(), Buffer.size(), &sender, &senderPort);

    if (_isCalling == false)
        UI.setResponse(Buffer.data());
    else {
        UI.setResponse("In call\n");
        listening(Buffer);
    }

    std::string receive = UI.getResponse()->text().toStdString();

    if (receive.compare("Hello from other client\n") == 0) {
        std::cout << "Incoming call..." << std::endl;
        _port = senderPort;
        _add = sender;
        _isCalling = true;
        _streamListen = _test.openStream();
        _test.startStream(_streamListen);
        _streamSpeak = _test.openStream();
        _test.startStream(_streamSpeak);
        _timerSpeak->start();
    }
}

void Client::initCall()
{
    if (UI.getAddress()->text() == "" || UI.getPort()->text() == "")
        return;

    QString qstr = QString::fromUtf8(UI.getAddress()->text().toStdString().c_str());
    QHostAddress addr(qstr);
    quint16 f_port(std::stoi(UI.getPort()->text().toStdString()));

    QByteArray Data;
    Data.append("Hello from other client\n");
    socket->writeDatagram(Data, addr, f_port);
    _add = addr;
    _port = f_port; //attention mtn parle a lautre client

    _streamSpeak = _test.openStream();
    _test.startStream(_streamSpeak);
    _streamListen = _test.openStream();
    _test.startStream(_streamListen);
    _timerSpeak->start();
    _isCalling = true;
}

void Client::speaking()
{
    std::vector<unsigned short> captured(BUFFER_SIZE * CHANNELS);
    std::vector<unsigned char> encoded(BUFFER_SIZE * CHANNELS * 2);
    QByteArray send;

    captured = _test.readStream(_streamSpeak);
    encoded = _test.encode(captured);
    send = reinterpret_cast<char*>(encoded.data());
    socket->writeDatagram(send, _add, _port);
}

void Client::listening(QByteArray Buffer)
{
    std::vector<unsigned short> decoded(BUFFER_SIZE * CHANNELS);
    std::vector<unsigned char> encoded(Buffer.data(), Buffer.data() + Buffer.size());
    
    decoded = _test.decode(encoded);
    _test.writeStream(_streamListen, decoded);
}