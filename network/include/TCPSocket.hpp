/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** TCPSocket.hpp
*/

#ifndef TCPSOCKET_HPP_
#define TCPSOCKET_HPP_

#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>

#include "Sockets.hpp"

#define MAX_RECV 1024

class TCPSocket
{
	public:
		TCPSocket();
		~TCPSocket();

        bool Bind(const std::string &ipaddress, unsigned short port);
        bool Connect(const std::string &ipaddress, unsigned short port);
        bool ListenOn(unsigned short port, unsigned short max_connections);

        int Send(const std::string data) const;
        int Read(std::string &data) const;
        int Recv(std::string &data, unsigned int len) const;

        // SOCKET getSocket() const noexcept;
        SOCKET sock;

    private:
        sockaddr_in InitAddr(const std::string &ipaddress, unsigned short port);

};

#endif /* !TCPSOCKET_HPP_ */
