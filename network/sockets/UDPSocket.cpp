/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** UDPSocket.cpp
*/

#include "UDPSocket.hpp"

UDPSocket::UDPSocket()
{
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        throw std::runtime_error("Invalid socket");
    }
}

UDPSocket::~UDPSocket()
{
    Sockets::CloseSocket(sock);
}

int UDPSocket::Send(const char *data, unsigned int len)
{
    return send(sock, data, len, 0);
}

int UDPSocket::Receive(char *buffer, unsigned int len)
{
    return recv(sock, buffer, len, 0);
}