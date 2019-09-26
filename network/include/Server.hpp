/*
** EPITECH PROJECT, 2019
** Server_CPP
** File description:
** Server
*/

#pragma once

#include <algorithm>
#include <arpa/inet.h>
#include <deque>
#include <memory>
#include <sys/socket.h>

#include "Socket.hpp"

#define DEFAULT_PORT 0

using sockaddr_in = struct sockaddr_in;
using socket_t = int;

class Client
{
    public:
        Client(Socket sock):
            _sock(sock) {}
        Socket _sock;
};

class Server
{
	public:
		Server(const int port);
		~Server() = default;

        void initMainSocket(const int);

        void add_sockets_to_set(socket_t *);

        void removeClient(Client);

        void poll();
        void run();
        void shutdown();

        void handleConnection();
        void handleReceive(Client);
        void solveRequest();

    private:
        bool _status;
        Socket _listen_sock;
        socket_t _sock;
        sockaddr_in _addr;
        // Socket _main_socket;
        fd_set _sock_set;
        std::deque<std::unique_ptr<Client>> _client_list;
};