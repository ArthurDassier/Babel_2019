/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** UDPSocket.cpp
*/

#include "UDPSocket.hpp"

/*!
 * \fn UDPSocket::UDPSocket()
 * \brief Socket is valid ?
 *
 * \param void
 */

UDPSocket::UDPSocket()
{
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    std::cout << "udp sock: " << sock << std::endl;
    if (sock == INVALID_SOCKET)
    {
        throw std::runtime_error("Invalid socket");
    }
}

/*!
 * \fn UDPSocket::~UDPSocket()
 * \brief Socket is valid ?
 *
 * \param void
 */

UDPSocket::~UDPSocket()
{
    Sockets::CloseSocket(sock);
}

/*!
 * \fn UDPSocket::Bind(unsigned short port)
 * \brief Socket is valid ?
 *
 * \param unsigned short port
 */

bool UDPSocket::Bind(unsigned short port)
{
    addr.sin_addr.s_addr = htonl(INADDR_ANY); //inet_addr(ipaddress.c_str());
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    return bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(addr));
}

/*!
 * \fn UDPSocket::Send(const char *data, unsigned int len)
 * \brief Socket is valid ?
 *
 * \param const char *data, unsigned int len
 */

int UDPSocket::Send(const char *data, unsigned int len)
{
    return send(sock, data, len, 0);
}

/*!
 * \fn UDPSocket::Read(std::string &data) const
 * \brief Socket is valid ?
 *
 * \param std::string &data
 */

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

/*!
 * \fn UDPSocket::Receive(char *buffer, unsigned int len)
 * \brief Socket is valid ?
 *
 * \param char *buffer, unsigned int len
 */

int UDPSocket::Receive(char *buffer, unsigned int len)
{
    return recv(sock, buffer, len, 0);
}

/*!
 * \fn UDPSocket::getAddr() const
 * \brief Socket is valid ?
 *
 * \param void
 */

sockaddr_in UDPSocket::getAddr() const
{
    return addr;
}