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
    std::cout << "udp sock: " << sock << std::endl;
    if (sock == INVALID_SOCKET)
    {
        throw std::runtime_error("Invalid socket");
    }
}

UDPSocket::~UDPSocket()
{
    Sockets::CloseSocket(sock);
}

bool UDPSocket::Bind(unsigned short port)
{
    addr.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr(ipaddress.c_str());
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    return bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
}

int UDPSocket::Send(const char *data, unsigned int len)
{
    return send(sock, data, len, 0);
}

int UDPSocket::Read(std::string &data) const
{
    char buffer[MAX_RECV + 1];
    int status = 0;

    memset(buffer, 0, MAX_RECV + 1);
    status = read(sock, buffer, MAX_RECV);
    if (status)
        data = buffer;
    return status;
}

int UDPSocket::Receive(char *buffer, unsigned int len)
{
    return recv(sock, buffer, len, 0);
}
sockaddr_in UDPSocket::getAddr() const
{
    return addr;
}