/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtClient
*/

#pragma once

#include <iostream>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QUdpSocket>
#include <QtCore/QObject>
#include <QtWidgets>
#include "unistd.h"
#include <thread>
#include <mutex>

#include "ClientInterface.hpp"
#include "PortAudio.hpp"

class Client : public QWidget
{
    Q_OBJECT
    public:
        explicit Client(std::string addr, int port, QObject *parent = 0);
        ~Client() = default;

        void listening(QByteArray Buffer);

    signals:

    public slots:
        void readyRead();
        void sendToServer();
        void initCall();
        void speaking();

    private:
        QUdpSocket *socket;
        QHostAddress _add;
        quint16 _port;

        bool _isCalling;
        bool _firstTime;

        PaStream *_streamSpeak;
        PaStream *_streamListen;

        QTimer *_timerSpeak;

        ClientInterface UI;
        testAudio _test;
};