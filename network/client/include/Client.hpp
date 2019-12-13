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

        void audioInput();
        void audioSend();
        void audioOutput();

        void testSon(); //a virer avant la fin c juste un test

    signals:


    public slots:
        void readyRead();
        void takeIp();
        void SaySomething();
        void tryToCall();

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

        PortAudio _sonSend;
        PortAudio _sonReceive;
        PaStream *_streamSend;
        PaStream *_streamReceive;

        testAudio _test;

        std::thread _threadInputSon;
        std::thread _threadSendSon;
        std::thread _threadOutputSon;
};