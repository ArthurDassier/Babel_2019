/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtClient
*/

#include "Client.hpp"

network::Client::Client(const std::string &addr, const int port, QObject *parent):
    QWidget(),
    _addr(QString::fromUtf8(addr.c_str())),
    _port(port),
    _isCalling(false),
    _timerSpeak(new QTimer()),
    UI(this)
{
    socket = new QUdpSocket(this);
    _timerSpeak->setInterval(1);
    
    setFixedSize(500, 250);
    setLayout(UI.renderInterface());
    setWindowTitle("Babel");

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(UI.getCommandButton(), SIGNAL(clicked()), this, SLOT(sendToServer()));
    connect(UI.getCallButton(), SIGNAL(clicked()), this, SLOT(initCall()));
    connect(_timerSpeak, SIGNAL(timeout()), this, SLOT(speaking()));
}

void network::Client::sendToServer()
{
    if (UI.getCommand()->text() == "")
        return;

    QString word = UI.getCommand()->text();
    QByteArray Data = word.toUtf8();

    socket->writeDatagram(Data, _addr, _port);
    std::cout << "Message sent: " <<
        UI.getCommand()->text().toStdString() << std::endl;
}

void network::Client::readyRead()
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
        _addr = sender;
        _isCalling = true;
        _listeningStream = AM.openStream();
        AM.startStream(_listeningStream);
        _speakingStream = AM.openStream();
        AM.startStream(_speakingStream);
        _timerSpeak->start();
    }
}

void network::Client::initCall()
{
    if (UI.getAddress()->text() == "" || UI.getPort()->text() == "")
        return;

    QString qstr = QString::fromUtf8(UI.getAddress()->text().toStdString().c_str());
    QHostAddress addr(qstr);
    quint16 f_port(std::stoi(UI.getPort()->text().toStdString()));

    QByteArray Data;
    Data.append("Hello from other client\n");
    socket->writeDatagram(Data, addr, f_port);
    _addr = addr;
    _port = f_port;

    _speakingStream = AM.openStream();
    AM.startStream(_speakingStream);
    _listeningStream = AM.openStream();
    AM.startStream(_listeningStream);
    _timerSpeak->start();
    _isCalling = true;
}

void network::Client::speaking()
{
    std::vector<unsigned short> captured(BUFFER_SIZE * CHANNELS);
    std::vector<unsigned char> encoded(BUFFER_SIZE * CHANNELS * 2);
    QByteArray send;

    captured = AM.readStream(_speakingStream);
    encoded = AM.encode(captured);
    send = reinterpret_cast<char*>(encoded.data());
    socket->writeDatagram(send, _addr, _port);
}

void network::Client::listening(QByteArray Buffer)
{
    std::vector<unsigned short> decoded(BUFFER_SIZE * CHANNELS);
    std::vector<unsigned char> encoded(Buffer.data(), Buffer.data() + Buffer.size());
    
    decoded = AM.decode(encoded);
    AM.writeStream(_listeningStream, decoded);
}