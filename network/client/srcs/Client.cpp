/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtClient
*/

#include "Client.hpp"

Client::Client(std::string addr, int port, QObject *parent):
    QWidget(),
    _isCalling(false)
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

    // _sonSend.SetInputParameters();
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
    if (_isCalling == false)
        _textResponse->setText(Buffer.data());
    else {
        _textResponse->setText("en appelle\n");
        // _sonSend.SetInputParameters();
        _sonSend.SetData(5, 44100, 2);
        _sonSend.SetOutputParameters();
        _sonSend.setDataFrameIndex();
        std::vector<unsigned short> decoded(Buffer.data(), Buffer.data() + Buffer.size());
        std::cout << "vector: " << decoded.data() << std::endl;
        _streamReceive = _sonSend.writeStream(decoded);
        _sonSend.PlayStream(_streamReceive);
        std::cout << "fin du play" << std::endl;
    }
    // std::string str(Buffer.data());
    // std::cout << str << std::endl;
    // if (str[0] == '@')
    //     tryToCall(str);
    // SaySomething();
    std::string receive = _textResponse->text().toStdString();

    if (receive.compare("Hello from other client\n") == 0) {
        std::cout << "qq veut call" << std::endl;
        _isCalling = true;
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

    /* test de port audio a la main */
    // PaStream* stream = nullptr;
    // int const bufferSize = 480;
    // std::vector<unsigned short> captured(bufferSize * 2);
    // PaError paErr;
    // int const sampleRate = 48000;
    // int const durationSeconds = 5;
    // int framesProcessed = 0;
    // if ((paErr = Pa_OpenDefaultStream(&stream,
    //     2, 2, paInt16, sampleRate,
    //     bufferSize, nullptr, nullptr)) != paNoError)
    // {
    //     std::cout << "Pa_OpenDefaultStream failed: " << Pa_GetErrorText(paErr) << "\n";
    // }
    // if ((paErr = Pa_StartStream(stream)) != paNoError) 
    // {
    //     std::cout << "Pa_StartStream failed: " << Pa_GetErrorText(paErr) << "\n";
    // }
    // if ((paErr = Pa_ReadStream(stream, 
    //     captured.data(), bufferSize)) != paNoError)
    // {
    //     std::cout << "Pa_ReadStream failed: " << Pa_GetErrorText(paErr) << "\n";
    // }
    // while (framesProcessed < sampleRate * durationSeconds)
    // {
    //     if ((paErr = Pa_ReadStream(stream, 
    //         captured.data(), bufferSize)) != paNoError)
    //     {
    //         std::cout << "Pa_ReadStream failed: " << Pa_GetErrorText(paErr) << "\n";
    //     }
    //     if ((paErr = Pa_WriteStream(stream, captured.data(), bufferSize)) != paNoError)
    //     {
    //         std::cout << "Pa_WriteStream failed: " << Pa_GetErrorText(paErr) << "\n";
    //     }
    //     framesProcessed += bufferSize;
    // }
    // if ((paErr = Pa_StopStream(stream)) != paNoError)
    // {
    //     std::cout << "Pa_StopStream failed: " << Pa_GetErrorText(paErr) << "\n";
    // }

    int opusErr;
    PaError paErr;
    std::string s;

    int const channels = 2;
    int const bufferSize = 480;
    int const sampleRate = 48000;
    int const durationSeconds = 5;

    int framesProcessed = 0;

    std::vector<unsigned short> captured(bufferSize * channels);
    std::vector<unsigned short> decoded(bufferSize * channels);
    // * 2: byte count, 16 bit samples
    std::vector<unsigned char> encoded(bufferSize * channels * 2);

    // initialize opus
    OpusEncoder* enc = opus_encoder_create(
        sampleRate, channels, OPUS_APPLICATION_AUDIO, &opusErr);
    if (opusErr != OPUS_OK)
    {
        std::cout << "opus_encoder_create failed: " << opusErr << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    OpusDecoder* dec = opus_decoder_create(
        sampleRate, channels, &opusErr);
    if (opusErr != OPUS_OK)
    {
        std::cout << "opus_decoder_create failed: " << opusErr << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    // initialize portaudio
    if ((paErr = Pa_Initialize()) != paNoError)
    {
        std::cout << "Pa_Initialize failed: " << Pa_GetErrorText(paErr) << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    PaStream* stream = nullptr;
    if ((paErr = Pa_OpenDefaultStream(&stream,
        channels, channels, paInt16, sampleRate,
        bufferSize, nullptr, nullptr)) != paNoError)
    {
        std::cout << "Pa_OpenDefaultStream failed: " << Pa_GetErrorText(paErr) << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    // start stream
    if ((paErr = Pa_StartStream(stream)) != paNoError) 
    {
        std::cout << "Pa_StartStream failed: " << Pa_GetErrorText(paErr) << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    // capture, encode, decode & render durationSeconds of audio
    while (framesProcessed < sampleRate * durationSeconds)
    {
        if ((paErr = Pa_ReadStream(stream, 
            captured.data(), bufferSize)) != paNoError)
        {
            std::cout << "Pa_ReadStream failed: " << Pa_GetErrorText(paErr) << "\n";
            std::getline(std::cin, s);
            return 1;
        }

        if ((enc_bytes = opus_encode(enc, reinterpret_cast<opus_int16 const*>(
            captured.data()), 480, encoded.data(), encoded.size())) < 0)
        {
            std::cout << "opus_encode failed: " << enc_bytes << "\n";
            std::getline(std::cin, s);
            return 1;
        }

        if ((dec_bytes = opus_decode(dec, encoded.data(), enc_bytes,
            reinterpret_cast<opus_int16*>(decoded.data()), 480, 0)) < 0)
        {
            std::cout << "opus_decode failed: " << dec_bytes << "\n";
            std::getline(std::cin, s);
            return 1;
        }

        if ((paErr = Pa_WriteStream(stream, decoded.data(), bufferSize)) != paNoError)
        {
            std::cout << "Pa_WriteStream failed: " << Pa_GetErrorText(paErr) << "\n";
            std::getline(std::cin, s);
            return 1;
        }

        framesProcessed += bufferSize;
    }

    // stop stream
    if ((paErr = Pa_StopStream(stream)) != paNoError)
    {
        std::cout << "Pa_StopStream failed: " << Pa_GetErrorText(paErr) << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    // cleanup portaudio
    if ((paErr = Pa_CloseStream(stream)) != paNoError) 
    {
        std::cout << "Pa_CloseStream failed: " << Pa_GetErrorText(paErr) << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    if ((paErr = Pa_Terminate()) != paNoError) 
    {
        std::cout << "Pa_Terminate failed: " << Pa_GetErrorText(paErr) << "\n";
        std::getline(std::cin, s);
        return 1;
    }

    // cleanup opus
    opus_decoder_destroy(dec);
    opus_encoder_destroy(enc);







    /* test avec port audio de ttt */
    // PaStream *stream;
    // _sonSend.SetInputParameters();
    // _sonSend.SetData(5, 44100, 2);
    // stream = _sonSend.RecordStream();
    // _sonSend.StartStream(stream);
    // Pa_Sleep(3000);
    // // Data.clear();
    // std::vector<unsigned short> dataS = _sonSend.readStream(stream);
    // PaStream *new_stream = _sonSend.writeStream(dataS);
    // _sonSend.PlayStream(new_stream);

    // // Data = reinterpret_cast<char*>(_sonSend.readStream(stream).data());
    // // socket->writeDatagram(Data, _add, _port);
    // _sonSend.CloseStream(stream);
    // _sonSend.SetOutputParameters();
    // _sonSend.setDataFrameIndex();
    // _sonSend.PlayStream(stream);
    // _streamSend = nullptr;

    // _threadInputSon = std::thread(&Client::audioInput, this);
    // _threadSendSon = std::thread(&Client::audioSend, this);
    // _threadOutputSon = std::thread(&Client::audioOutput, this);

    // PaStream *stream;
    // _sonSend.SetInputParameters();
    // std::cout << "1" << std::endl;
    // _sonSend.SetData(5, 44100, 2);
    // std::cout << "2" << std::endl;
    // stream = _sonSend.RecordStream();
    // std::cout << "3" << std::endl;
    // _sonSend.StartStream(stream);
    // std::cout << "4" << std::endl;
    // Pa_Sleep(3000);
    // std::cout << "5" << std::endl;
    // _sonSend.CloseStream(stream);
    // std::cout << "6" << std::endl;
    // _sonSend.SetOutputParameters();
    // _sonSend.setDataFrameIndex();
    // std::cout << "7" << std::endl;
    // _sonSend.PlayStream(stream);
    // std::cout << "8" << std::endl;
    // _sonSend.StartStream(stream);
    // Pa_Sleep(3000);
    // std::cout << "9" << std::endl;
    // _sonSend.CloseStream(stream);
    // std::cout << "10" << std::endl;
}

void Client::takeIp()
{
    std::cout << "adresse ip: " << _lineAddress->text().toStdString() << std::endl;
    std::cout << "port: " << _linePort->text().toStdString() << std::endl;
}

void Client::audioInput()
{
    QByteArray Data;
    QString word;

    _sonSend.SetInputParameters();
    while (1) {
        usleep(2000000);
        _sonSend.SetData(5, 44100, 2);
        _streamSend = _sonSend.RecordStream();
        _sonSend.StartStream(_streamSend);
        Pa_Sleep(3000);
        _sonSend.CloseStream(_streamSend);
        word = (const char*)_streamSend;
        Data = word.toUtf8();
        socket->writeDatagram(Data, _add, _port);
    }
}

void Client::audioSend()
{
    while (1) {
        usleep(2000000);
        QByteArray Data;
        QString word = (const char*)_streamSend;
        Data = word.toUtf8();
        socket->writeDatagram(Data, _add, _port);
    }
}

void Client::audioOutput()
{
    _sonSend.SetOutputParameters();
    _sonSend.setDataFrameIndex();
    while (1) {
        QString str = _textResponse->text();
        _streamReceive = (void *) str.toStdString().c_str();
        _sonSend.PlayStream(_streamReceive);
        // usleep(1000000);
    }
}

void Client::testSon()
{
    PaStream *stream;
    _sonSend.SetInputParameters();
    // _sonReceive.SetInputParameters();
    while (1) {
        // PaStream *stream;
        // _sonSend.SetInputParameters();
        std::cout << "1" << std::endl;
        _sonSend.SetData(5, 44100, 2);
        std::cout << "2" << std::endl;
        stream = _sonSend.RecordStream();
        std::cout << "3" << std::endl;
        _sonSend.StartStream(stream);
        std::cout << "4" << std::endl;
        Pa_Sleep(3000);
        std::cout << "5" << std::endl;
        _sonSend.CloseStream(stream);
        std::cout << "6" << std::endl;
        _sonReceive.SetOutputParameters();
        _sonReceive.setDataFrameIndex();
        std::cout << "7" << std::endl;
        _sonReceive.PlayStream(stream);
        std::cout << "8" << std::endl;
        _sonSend.StartStream(stream);
        Pa_Sleep(3000);
        std::cout << "9" << std::endl;
        _sonSend.CloseStream(stream);
        std::cout << "10" << std::endl;
    }
}