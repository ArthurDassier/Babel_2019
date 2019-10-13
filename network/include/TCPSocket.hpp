/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** TCPSocket.hpp
*/

#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <unistd.h>

#include "Sockets.hpp"

#define MAX_RECV 1024

/*! \class TCPSocket
* \brief Class representing the TCPSocket
*
*  This class handle the differents sockets
*/

class TCPSocket
{
	public:
		TCPSocket();
		~TCPSocket();

        bool Accept(const int socket, sockaddr_in &addr);
        bool Bind(const std::string &ipaddress, unsigned short port);
        bool Connect(const std::string &ipaddress, unsigned short port);
        bool ListenOn(unsigned short port, unsigned short max_connections);

        int Send(const std::string data) const;
        int Read(std::string &data) const;
        int Recv(std::string &data, unsigned int len) const;

        SOCKET sock;

    private:
        sockaddr_in InitAddr(const std::string &ipaddress, unsigned short port);

};