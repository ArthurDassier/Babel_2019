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
    // socket->bind(QHostAddress::LocalHost, 4086);
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

std::string uCharToChar(std::vector<unsigned char> tab)
{
    std::vector<char> res;
    for (int i = 0; i < tab.size(); i++) {
        if (tab[i] == 0) {
            res.push_back(2);
            res.push_back(6);
        } else {
            res.push_back(1);
            res.push_back(tab[i]);
        }
    }
    return (std::string(res.data()));
}

std::vector<unsigned char> charToUChar(std::string str)
{
    std::vector<unsigned char> res;
    for (int i = 0; i < str.size(); i++) {
        if (i % 2 == 0 && i + 1 < str.size()) {
            if (str[i] == 1)
                res.push_back(str[i + 1]);
            else
                res.push_back(0);
        }
    }
    return (res);
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
        // PaStream *stream = _test.openStream();
        // _test.startStream(stream);

        std::string str = Buffer.toStdString();
        std::vector<unsigned char> encoded(str.begin(), str.end()); //ici pour le recu
        std::vector<unsigned char> decode_char = charToUChar(str);
        std::vector<unsigned short> decoded = _test.decode(decode_char);
        std::cout << "decoded: ";
        for (auto const& c : decoded)
            std::cout << c << ' ';
        _test.writeStream(_stream, decoded);

        // std::vector<unsigned short> decoded(BUFFER_SIZE * CHANNELS);
        // opus_int32 dec_bytes;
        // std::vector<unsigned char> encoded(Buffer.data(), Buffer.data() + Buffer.size());
        // decoded = _test.decode(encoded);
        // std::cout << "~DECODED " << Buffer.size() << std::endl;
        // _test.writeStream(stream, decoded);
        std::cout << "fin du play" << std::endl;
        // _test.stopStream(stream);
        // _test.closeStream(stream);

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
        _stream = _test.openStream();
        _test.startStream(_stream);
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

    // int opusErr;
    // PaError paErr;
    // std::string s;

    // int const channels = 2;
    // int const bufferSize = 480;
    // int const sampleRate = 48000;
    // int const durationSeconds = 5;

    // opus_int32 enc_bytes;
    // opus_int32 dec_bytes;
    // int framesProcessed = 0;

    // std::vector<unsigned short> captured(bufferSize * channels);
    // std::vector<unsigned short> decoded(bufferSize * channels);
    // // * 2: byte count, 16 bit samples
    // std::vector<unsigned char> encoded(bufferSize * channels * 2);

    // // initialize opus
    // OpusEncoder* enc = opus_encoder_create(
    //     sampleRate, channels, OPUS_APPLICATION_AUDIO, &opusErr);
    // if (opusErr != OPUS_OK)
    // {
    //     std::cout << "opus_encoder_create failed: " << opusErr << "\n";
    // }

    // OpusDecoder* dec = opus_decoder_create(
    //     sampleRate, channels, &opusErr);
    // if (opusErr != OPUS_OK)
    // {
    //     std::cout << "opus_decoder_create failed: " << opusErr << "\n";
    // }

    // // initialize portaudio
    // if ((paErr = Pa_Initialize()) != paNoError)
    // {
    //     std::cout << "Pa_Initialize failed: " << Pa_GetErrorText(paErr) << "\n";
    // }

    // PaStream* stream = nullptr;
    // if ((paErr = Pa_OpenDefaultStream(&stream,
    //     channels, channels, paInt16, sampleRate,
    //     bufferSize, nullptr, nullptr)) != paNoError)
    // {
    //     std::cout << "Pa_OpenDefaultStream failed: " << Pa_GetErrorText(paErr) << "\n";
    // }

    // // start stream
    // if ((paErr = Pa_StartStream(stream)) != paNoError) 
    // {
    //     std::cout << "Pa_StartStream failed: " << Pa_GetErrorText(paErr) << "\n";
    // }

    // // capture, encode, decode & render durationSeconds of audio
    // while (framesProcessed < sampleRate * durationSeconds)
    // {
    //     if ((paErr = Pa_ReadStream(stream, 
    //         captured.data(), bufferSize)) != paNoError)
    //     {
    //         std::cout << "Pa_ReadStream failed: " << Pa_GetErrorText(paErr) << "\n";
    //     }

    //     if ((enc_bytes = opus_encode(enc, reinterpret_cast<opus_int16 const*>(
    //         captured.data()), 480, encoded.data(), encoded.size())) < 0)
    //     {
    //         std::cout << "opus_encode failed: " << enc_bytes << "\n";
    //     }

    //     if ((dec_bytes = opus_decode(dec, encoded.data(), enc_bytes,
    //         reinterpret_cast<opus_int16*>(decoded.data()), 480, 0)) < 0)
    //     {
    //         std::cout << "opus_decode failed: " << dec_bytes << "\n";
    //     }

    //     if ((paErr = Pa_WriteStream(stream, decoded.data(), bufferSize)) != paNoError)
    //     {
    //         std::cout << "Pa_WriteStream failed: " << Pa_GetErrorText(paErr) << "\n";
    //     }

    //     framesProcessed += bufferSize;
    // }

    // // stop stream
    // if ((paErr = Pa_StopStream(stream)) != paNoError)
    // {
    //     std::cout << "Pa_StopStream failed: " << Pa_GetErrorText(paErr) << "\n";
    // }

    // // cleanup portaudio
    // if ((paErr = Pa_CloseStream(stream)) != paNoError) 
    // {
    //     std::cout << "Pa_CloseStream failed: " << Pa_GetErrorText(paErr) << "\n";
    // }

    // if ((paErr = Pa_Terminate()) != paNoError) 
    // {
    //     std::cout << "Pa_Terminate failed: " << Pa_GetErrorText(paErr) << "\n";
    // }

    // // cleanup opus
    // opus_decoder_destroy(dec);
    // opus_encoder_destroy(enc);


    // testAudio test;
    PaStream *stream;
    // std::vector<unsigned short> captured(BUFFER_SIZE * CHANNELS);
    std::vector<unsigned short> decoded(BUFFER_SIZE * CHANNELS);
    // std::vector<unsigned char> encoded(BUFFER_SIZE * CHANNELS * 2);
    opus_int32 dec_bytes;
    int i = 0;
    QByteArray send;

    stream = _test.openStream();
    _test.startStream(stream);

    while (i < SAMPLE_RATE * 5) { //5-> les secondes que ca dure
        std::string msg("");
        std::vector<unsigned short> captured = _test.readStream(stream);
        std::cout << "captured: ";
        for (auto const& c : captured)
            std::cout << c << ' ';
        std::vector<unsigned char> encoded = _test.encode(captured);
        std::string encoded_msg(encoded.begin(), encoded.end());
        msg += encoded_msg;
        std::string new_msg = uCharToChar(encoded);//char(6) + uCharToChar(encoded);
        QByteArray NewData;
        NewData.append(new_msg.c_str());
        socket->writeDatagram(NewData, _add, _port);
        // captured = _test.readStream(stream);
        // encoded = _test.encode(captured);
        /* envoyer */
        // send = reinterpret_cast<char*>(encoded.data());
        // socket->writeDatagram(send, _add, _port);

        // std::vector<unsigned char> decode_char = charToUChar(new_msg);
        // std::vector<unsigned short> decoded = _test.decode(decode_char);

        // decoded = _test.decode(encoded);
        // _test.writeStream(stream, decoded);
        i += BUFFER_SIZE;
    }
    _test.stopStream(stream);
    _test.closeStream(stream);
    // test.~testAudio();



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
