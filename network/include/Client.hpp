/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client.hpp
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <thread>

#include "Packet.hpp"
#include "TCPSocket.hpp"
#include "UDPSocket.hpp"

class Client {
    public:
        Client(); //(const std::string ip, unsigned short port);
        ~Client();

    public:
        void connectToServer(const std::string ip, unsigned short port);

        void initStreaming();
        static void openStream();
        static void sendStream();

        // void onNewConnection();
        // void onSocketStateChanged();
        // void onReadyRead();

        void sendMessage(const int clientfd, const std::string msg);

        static void askForCall(UDPSocket);

        void run();

    private:
        void initListener(int sockfd);
        static void Listener(int, UDPSocket);
        static void UDPListener(UDPSocket client);

        utils::Packet _packet;
        TCPSocket _socket;
        UDPSocket _udp;
};

#endif /* !CLIENT_HPP_ */