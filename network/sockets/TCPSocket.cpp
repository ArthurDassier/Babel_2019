/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** TCPSocket.cpp
*/

#include "TCPSocket.hpp"

TCPSocket::TCPSocket()
{
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        // std::ostringstream error;
        // error << "Erreur initialisation socket [" << Sockets::GetError() << "]";
        // throw std::runtime_error(error.str());
        throw std::runtime_error("Invalid socket");
    }
}

TCPSocket::~TCPSocket()
{
    Sockets::CloseSocket(sock);
}

bool TCPSocket::Connect(const std::string &ipaddress, unsigned short port)
{
    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ipaddress.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    return connect(sock, reinterpret_cast<sockaddr*>(&server), sizeof(server)) == 0;
}

int TCPSocket::Send(const char *data, unsigned int len)
{
    return send(sock, data, len, 0);
}

int TCPSocket::Receive(char *buffer, unsigned int len)
{
    return recv(sock, buffer, len, 0);
}

SOCKET TCPSocket::getSocket() const noexcept
{
    return sock;
}