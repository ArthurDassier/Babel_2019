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

namespace network {
    class Client : public QWidget
    {
        Q_OBJECT
        public:
            explicit Client(const std::string &addr, const int port, QObject *parent = nullptr);
            ~Client() = default;

            void listening(QByteArray Buffer);

        signals:

        public slots:
            void readyRead();
            void sendToServer();
            void initCall();
            void speaking();

        private:
            QUdpSocket      *socket;
            QHostAddress    _addr;
            quint16         _port;
            bool            _isCalling;

            PaStream    *_speakingStream;
            PaStream    *_listeningStream;
            QTimer      *_timerSpeak;

            ui::ClientInterface UI;
            audio::AudioManager AM;
    };
}; // namespace network