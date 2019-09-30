/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

class Client {
    public:
        Client();
        ~Client();

    public:
        void onNewConnection();
        void onSocketStateChanged();
        void onReadyRead();

    private:
        // QTcpServer _server;
        // QList<QTcpSocket *> _sockets;
};

#endif /* !CLIENT_HPP_ */