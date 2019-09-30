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

sockaddr_in TCPSocket::InitAddr(const std::string &ipaddress, unsigned short port)
{
    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ipaddress.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    return server;
}

bool TCPSocket::Bind(const std::string &ipaddres, unsigned short port)
{
    // sockaddr_in server;
    // server.sin_addr.s_addr = inet_addr(ipaddress.c_str());
    // server.sin_family = AF_INET;
    // server.sin_port = htons(port);
    // return bind(sock, reinterpret_cast<sockaddr *>(&server), sizeof(server));
}

bool TCPSocket::Connect(const std::string &ipaddress, unsigned short port)
{
    sockaddr_in server;
    server.sin_addr.s_addr = inet_addr(ipaddress.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    // sockaddr_in server = InitAddr(ipaddress, port);
    return connect(sock, reinterpret_cast<sockaddr *>(&server), sizeof(server)) == 0;
}

bool TCPSocket::ListenOn(unsigned short port, unsigned short max_connections)
{
    // sockaddr_in server = InitAddr(INADDR_ANY, port);
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

int TCPSocket::Send(const std::string data) const
{
    return send(sock, data.c_str(), data.size(), 0);
}

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

// SOCKET TCPSocket::getSocket() const noexcept
// {
//     return sock;
// }