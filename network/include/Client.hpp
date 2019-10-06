/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client.hpp
*/

#pragma once

#include <iostream>
#include <map>
#include <thread>

#include "ClientActions.hpp"
#include "Packet.hpp"
#include "TCPSocket.hpp"
#include "UDPSocket.hpp"

namespace cli
{
    struct props_s
    {
        std::string username;
        TCPSocket socket;
    };

    using props_p = std::unique_ptr<props_s>;
    using socket_p = std::unique_ptr<TCPSocket>;
    using action_f = std::function<void(TCPSocket *, props_p)>;
    using action_map = std::map<const std::string, action_f>;

    class Client
    {
        public:
            Client();
            ~Client();

            bool auth();
            bool connection(const std::string &ip, const std::string &port, const std::string &name);
            bool connectToServer(const std::string &ip, unsigned short port);

            void run();

            void initStreaming();
            static void openStream();
            static void sendStream();

            void sendMessage(const int clientfd, const std::string &msg);

            static void askForCall(UDPSocket);
            static void sendInfos(TCPSocket *, props_p);
            static void newConnection(TCPSocket *, props_p);

        private:
            void initActions();
            void initListener(TCPSocket *);
            static void listener(TCPSocket *, UDPSocket, props_p infos, action_map);
            static void UDPListener(UDPSocket client);

            static void handleReceive(TCPSocket *, const utils::pt, props_p, std::unique_ptr<action_map>);

            void setIsConnected(const bool &);
            bool getIsConnected() const noexcept;

            action_map _fMap;

            static utils::pt _recvJson;
            bool _isConnected;
            props_s _props;
            utils::Packet _packet;
            TCPSocket _socket;
            UDPSocket _udp;
    };

}; // namespace cli