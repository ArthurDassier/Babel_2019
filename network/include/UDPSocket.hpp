/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** UDPSocket.hpp
*/

#ifndef UDPSOCKET_HPP_
#define UDPSOCKET_HPP_

#include <iostream>
#include <string>
#include <string.h>

#include "Sockets.hpp"

#define MAX_RECV 1024

class UDPSocket
{
	public:
		UDPSocket();
		~UDPSocket();

        bool Bind(unsigned short port);

        int Send(const char *data, unsigned int len);
        // int Read(const std::string) const;
        int Read(std::string &data) const;
        int Receive(char *buffer, unsigned int len);

        sockaddr_in getAddr() const;

        SOCKET sock;
        sockaddr_in addr;
    private:
};

#endif /* !UDPSOCKET_HPP_ */