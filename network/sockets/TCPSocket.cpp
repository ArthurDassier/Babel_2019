/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** TCPSocket.cpp
*/

#include "TCPSocket.hpp"

/*!
 * \fn TCPSocket::~TCPSocket()
 * \brief Socket is valid ?
 *
 * \param void
 */


TCPSocket::TCPSocket()
{
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        throw std::runtime_error("Invalid socket");
    }
}

/*!
 * \fn TCPSocket::~TCPSocket()
 * \brief Socket is valid ?
 *
 * \param void
 */

TCPSocket::~TCPSocket()
{
    Sockets::CloseSocket(sock);
}

/*!
 * \fn TCPSocket::Accept(const int socket, sockaddr_in &addr)
 * \brief Socket is valid ?
 *
 * \param const int socket, sockaddr_in &addr
 */


bool TCPSocket::Accept(const int socket, sockaddr_in &addr)
{
    socklen_t addrlen = sizeof(addr);

    sock = accept(socket, (sockaddr *)&addr, &addrlen);
    return sock ? true : false;
}

/*!
 * \fn TCPSocket::InitAddr(const std::string &ipaddress, unsigned short port)
 * \brief Socket is valid ?
 *
 * \param const std::string &ipaddress, unsigned short port
 */


sockaddr_in TCPSocket::InitAddr(const std::string &ipaddress, unsigned short port)
{
    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ipaddress.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    return server;
}

/*!
 * \fn TCPSocket::Bind(const std::string &ipaddres, unsigned short port)
 * \brief Socket is valid ?
 *
 * \param const std::string &ipaddres, unsigned short port
 */


bool TCPSocket::Bind(const std::string &ipaddres, unsigned short port)
{
    // sockaddr_in server;
    // server.sin_addr.s_addr = inet_addr(ipaddress.c_str());
    // server.sin_family = AF_INET;
    // server.sin_port = htons(port);
    // return bind(sock, reinterpret_cast<sockaddr *>(&server), sizeof(server));
}

/*!
 * \fn TCPSocket::Connect(const std::string &ipaddress, unsigned short port)
 * \brief Socket is valid ?
 *
 * \param const std::string &ipaddress, unsigned short port
 */


bool TCPSocket::Connect(const std::string &ipaddress, unsigned short port)
{
    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ipaddress.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    return connect(sock, reinterpret_cast<sockaddr *>(&server), sizeof(server)) == 0;
}

/*!
 * \fn TCPSocket::ListenOn(unsigned short port, unsigned short max_connections)
 * \brief Socket is valid ?
 *
 * \param unsigned short port, unsigned short max_connections
 */


bool TCPSocket::ListenOn(unsigned short port, unsigned short max_connections)
{
    int ret = 0;
    sockaddr_in server;

    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    ret = bind(sock, reinterpret_cast<sockaddr *>(&server), sizeof(server));
    if (ret == -1)
        return false;
    std::cout << "lol" << std::endl;
    ret = listen(sock, max_connections);
    if (ret == -1)
        return false;
    std::cout << "double lol : " << ret << std::endl;
    return true;
}

/*!
 * \fn TCPSocket::Send(const std::string data) const
 * \brief Socket is valid ?
 *
 * \param const std::string data
 */


int TCPSocket::Send(const std::string data) const
{
    return send(sock, data.c_str(), data.size(), 0);
}

/*!
 * \fn TCPSocket::Read(std::string &data) const
 * \brief Socket is valid ?
 *
 * \param std::string &data
 */


int TCPSocket::Read(std::string &data) const
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
 * \fn TCPSocket::Recv(std::string &data, unsigned int len) const
 * \brief Socket is valid ?
 *
 * \param std::string &data, unsigned int len
 */


int TCPSocket::Recv(std::string &data, unsigned int len) const
{
    char buffer[MAX_RECV + 1];
    int status = 0;

    memset(buffer, 0, MAX_RECV + 1);
    status = recv(sock, buffer, MAX_RECV, 0);
    if (status)
        data = buffer;
    return status >= 0 ? status : 0;
}