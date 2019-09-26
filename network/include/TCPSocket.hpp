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

#include "Sockets.hpp"

class TCPSocket
{
	public:
		TCPSocket();
		~TCPSocket();

        bool Connect(const std::string &ipaddress, unsigned short port);

        int Send(const char *data, unsigned int len);
        int Receive(char *buffer, unsigned int len);

        SOCKET getSocket() const noexcept;

    private:
        SOCKET sock;
};

#endif /* !TCPSOCKET_HPP_ */
