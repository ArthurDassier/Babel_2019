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

#include "PortAudio.hpp"

class Client : public QWidget
{
    Q_OBJECT
    public:
        explicit Client(std::string addr, int port, QObject *parent = 0);
        ~Client();

    signals:


    public slots:
        void readyRead();
        void takeIp();
        void SaySomething();
        void tryToCall();
        void speaking();
        void listening(QByteArray Buffer);

    private:
        QUdpSocket *socket;
        QHostAddress _add;
        quint16 _port;

        QLabel *_labelResponse;
        QLabel *_textResponse;
        QFormLayout *_responseLayout;

        QLabel *_labelCommand;
        QLineEdit *_lineCommand;
        QFormLayout *_commandLayout;
        QPushButton *_buttonCommand;

        QLabel *_labelPort;
        QLineEdit *_linePort;
        QLabel *_labelAddress;
        QLineEdit *_lineAddress;
        QFormLayout *_callLayout;
        QPushButton *_buttonCall;

        QGridLayout *_gridLayout;

        bool _isCalling;
        bool _firstTime;

        PaStream *_streamSpeak;
        PaStream *_streamListen;

        testAudio _test;
};