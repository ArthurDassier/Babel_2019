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
    _firstTime(true)
{
    socket = new QUdpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    QString str = QString::fromUtf8(addr.c_str());
    _add = str;
    _port = port;

    setFixedSize(500, 250);
    _buttonCall = new QPushButton("Call", this);
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

Client::~Client()
{
    // _sonSend.~PortAudio();
}

void Client::SaySomething()
{
    if (_lineCommand->text() == "")
        return;

    QByteArray Data;
    QString word = _lineCommand->text();

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

    if (_isCalling == false)
        _textResponse->setText(Buffer.data());
    else {
        _textResponse->setText("en appelle\n");
        // PaStream *stream = _test.openStream();
        // _test.startStream(stream);

        // std::string str = Buffer.toStdString();
        // std::vector<unsigned char> encoded(str.begin(), str.end()); //ici pour le recu
        // std::vector<unsigned char> decode_char = charToUChar(str);
        // std::vector<unsigned short> decoded = _test.decode(decode_char);
        // std::cout << "decoded: ";
        // for (auto const& c : decoded)
        //     std::cout << c << ' ';
        // _test.writeStream(_stream, decoded);

        // std::vector<unsigned short> decoded(BUFFER_SIZE * CHANNELS);
        // opus_int32 dec_bytes;
        // std::vector<unsigned char> encoded(Buffer.data(), Buffer.data() + Buffer.size());
        // decoded = _test.decode(encoded);
        // std::cout << "~DECODED " << Buffer.size() << std::endl;
        // _test.writeStream(_stream, decoded);
        // std::cout << "fin du play" << std::endl;
        listening(Buffer);
    }

    std::string receive = _textResponse->text().toStdString();

    if (receive.compare("Hello from other client\n") == 0) {
        std::cout << "qq veut call" << std::endl;
        _port = senderPort;
        _add = sender;
        _isCalling = true;
        _streamListen = _test.openStream();
        _test.startStream(_streamListen);
    }
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
    _add = addr;
    _port = f_port; //attention mtn parle a lautre client

    // PaStream *stream;
    // std::vector<unsigned short> captured(BUFFER_SIZE * CHANNELS);
    // std::vector<unsigned short> decoded(BUFFER_SIZE * CHANNELS);
    // std::vector<unsigned char> encoded(BUFFER_SIZE * CHANNELS * 2);
    // opus_int32 dec_bytes;
    // int i = 0;
    // QByteArray send;

    // stream = _test.openStream();
    // _test.startStream(stream);

    // while (i < SAMPLE_RATE * 5) { //5-> les secondes que ca dure
    //     // std::string msg("");
    //     // std::vector<unsigned short> captured = _test.readStream(stream);
    //     // std::cout << "captured: ";
    //     // for (auto const& c : captured)
    //     //     std::cout << c << ' ';
    //     // std::vector<unsigned char> encoded = _test.encode(captured);
    //     // std::string encoded_msg(encoded.begin(), encoded.end());
    //     // msg += encoded_msg;
    //     // std::string new_msg = uCharToChar(encoded);//char(6) + uCharToChar(encoded);
    //     // QByteArray NewData;
    //     // NewData.append(new_msg.c_str());
    //     // socket->writeDatagram(NewData, _add, _port);
    //     captured = _test.readStream(stream);
    //     encoded = _test.encode(captured);
    //     /* envoyer */
    //     send = reinterpret_cast<char*>(encoded.data());
    //     socket->writeDatagram(send, _add, _port);

    //     // std::vector<unsigned char> decode_char = charToUChar(new_msg);
    //     // std::vector<unsigned short> decoded = _test.decode(decode_char);

    //     // decoded = _test.decode(encoded);
    //     // _test.writeStream(stream, decoded);
    //     i += BUFFER_SIZE;
    // }
    // _test.stopStream(stream);
    // _test.closeStream(stream);
}

void Client::speaking()
{
    std::vector<unsigned short> captured(BUFFER_SIZE * CHANNELS);
    std::vector<unsigned char> encoded(BUFFER_SIZE * CHANNELS * 2);
    QByteArray send;
    _streamSpeak = _test.openStream();
    _test.startStream(_streamSpeak);

    while (1) { //5-> les secondes que ca dure
        captured = _test.readStream(_streamSpeak);
        encoded = _test.encode(captured);
        send = reinterpret_cast<char*>(encoded.data());
        socket->writeDatagram(send, _add, _port);
    }
    _test.stopStream(_streamSpeak);
    _test.closeStream(_streamSpeak);
}

void Client::listening(QByteArray Buffer)
{
    std::vector<unsigned short> decoded(BUFFER_SIZE * CHANNELS);
    opus_int32 dec_bytes;
    std::vector<unsigned char> encoded(Buffer.data(), Buffer.data() + Buffer.size());
    decoded = _test.decode(encoded);
    std::cout << "~DECODED " << Buffer.size() << std::endl;
    _test.writeStream(_streamListen, decoded);
    std::cout << "fin du play" << std::endl;
}

void Client::takeIp()
{
    std::cout << "adresse ip: " << _lineAddress->text().toStdString() << std::endl;
    std::cout << "port: " << _linePort->text().toStdString() << std::endl;
}
