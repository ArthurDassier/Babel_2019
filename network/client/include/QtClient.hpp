/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** QtClient
*/

#pragma once

#include <QtNetwork/QTcpSocket>
#include <QtCore/QObject>

// class Client : public QObject
// {
//     Q_OBJECT
//     public:
//         explicit Client(QObject *parent = 0);
//         ~Client(){};
//         void SayHello();

//         void initSocket();
//         void readPendingDatagrams();

//     signals:

//     public slots:
//         void readyRead();

//     private:
//         QUdpSocket *socket;
// };


class MyTcpSocket : public QObject
{
    Q_OBJECT
    public:
        explicit MyTcpSocket(QObject *parent = 0);

        void doConnect();

    signals:

    public slots:
        void connected();
        void disconnected();
        void bytesWritten(qint64 bytes);
        void readyRead();

    private:
        QTcpSocket *socket;
};