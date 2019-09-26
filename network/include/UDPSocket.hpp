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

#include "Sockets.hpp"

class UDPSocket
{
	public:
		UDPSocket();
		~UDPSocket();

        int Send(const char *data, unsigned int len);
        int Receive(char *buffer, unsigned int len);

    private:
        SOCKET sock;
};

#endif /* !UDPSOCKET_HPP_ */