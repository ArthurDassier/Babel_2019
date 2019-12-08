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

class Client : public QObject
{
    Q_OBJECT
    public:
        explicit Client(QObject *parent = 0);
        ~Client(){};
        void SaySomething();

        void initSocket();
        void readPendingDatagrams();

    signals:

    public slots:
        void readyRead();

    private:
        QUdpSocket *socket;
};