/*
** EPITECH PROJECT, 2019
** Server_CPP
** File description:
** Socket
*/

#include "Socket.hpp"

Socket::Socket():
    _sock(-1)
{
    memset(&_addr, 0, sizeof(_addr));
}

bool Socket::create()
{
    int on = 1;

    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (!is_valid()) {
        perror("socket() failed");
        return false;
    }
    if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&on, sizeof(on))) {
        perror("setsockopt() failed");
        return false;
    }
    return true;
}

bool Socket::bind(const int port, uint32_t addr, uint32_t family)
{
    int ret_value = 0;

    if (!is_valid())
        return false;
    _addr.sin_addr.s_addr = htonl(addr);
    _addr.sin_family = family;
    _addr.sin_port = htons(port);
    ret_value = ::bind(_sock, (struct sockaddr *)&_addr, sizeof(_addr));
    if (ret_value == -1) {
        perror("bind() failed");
        return false;
    }
    std::cout << "bind: all good" << std::endl;
    return true;
}

bool Socket::listen() const
{
    int ret_value = 0;

    if (!is_valid())
        return false;
    ret_value = ::listen(_sock, MAX_CONNECTIONS);
    if (ret_value == -1) {
        perror("listen() failed");
        return false;
    }
    std::cout << "listen: all good" << std::endl;
    return true;
}

bool Socket::accept(Socket &new_socket) const
{
    int addr_len = sizeof(_addr);

    new_socket._sock = ::accept(_sock, (sockaddr *)&_addr, (socklen_t *)&addr_len);
    if (new_socket._sock <= 0)
        return false;
    std::cout << "accept: all good" << std::endl;
    return true;
}

bool Socket::send(const std::string msg) const
{
    int status = ::send(_sock, msg.c_str(), msg.size(), 0);
    if (status == -1)
        return false;
    return true;
}

int Socket::read(std::string &s) const
{
    char buffer[MAX_RECV + 1];
    int status;

    memset(buffer, 0, MAX_RECV + 1);
    status = ::read(_sock, buffer, MAX_RECV);
    // if (status == -1) {
    //     std::cout << "status == -1 errno == " << errno << " in Socket::recv\n";
    //     return 0;
    if (status == 0)
        return 0;
    else {
        s = buffer;
        return status;
    }
}

int Socket::recv(std::string &s) const
{
    char buf[MAX_RECV + 1];
    int status;
    s = "";

    memset(buf, 0, MAX_RECV + 1);
    status = ::recv(_sock, buf, MAX_RECV, 0);
    if (status == -1) {
        std::cout << "status == -1 errno == " << errno << " in Socket::recv\n";
        return 0;
    }
    else if (status == 0)
        return 0;
    else {
        s = buf;
        return status;
    }
}

bool Socket::connect(const std::string host, const int port)
{
    int status = 0;
    if (!is_valid())
        return false;
    _addr.sin_family = AF_INET;
    _addr.sin_port = htons(port);
    status = inet_pton(AF_INET, host.c_str(), &_addr.sin_addr);
    if (errno == EAFNOSUPPORT)
        return false;
    status = ::connect(_sock, (sockaddr *)&_addr, sizeof(_addr));
    if (status == 0)
        return true;
    return false;
}

bool Socket::is_valid() const
{
    return _sock != -1;
}

// void Socket::set_non_blocking(const bool b)
// {
//     int opts;

//     opts = fcntl(_sock, F_GETFL);

//     if (opts < 0)
//         return;

//     if (b)
//         opts = (opts | O_NONBLOCK);
//     else
//         opts = (opts & ~O_NONBLOCK);

//     fcntl(m_sock, F_SETFL, opts);
// }

// Socket::Socket(int port = DEFAULT_PORT):
//     _port(port)
// {
// }

// Socket::~Socket()
// {
//     close(_socket);
// }


// void Socket::bindSocket(void)
// {
//     if (bind(_socket, (sockaddr *) &_addr, sizeof(sockaddr_in)) == -1) {
//         perror("bind() failed");
//         exit(84);
//     }
// }

// void Socket::listenSocket(void)
// {
//     if (listen(_socket, 5) == -1) {
//         perror("listen() failed");
//         exit(84);
//     }
// }

// void Socket::initSocketAddr(int port)
// {
//     _addr.sin_addr.s_addr = htonl(INADDR_ANY);
//     _addr.sin_family = AF_INET;
//     _addr.sin_port = ntohs(port);
// }

// void Socket::initSocketAddr(void)
// {
//     _addr.sin_addr.s_addr = htonl(INADDR_ANY);
//     _addr.sin_family = AF_INET;
//     _addr.sin_port = ntohs(_port);
// }

// void Socket::setSocketOptions(void)
// {
//     int on = 1;

//     if (setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR,
//     (char *)&on, sizeof(on)) < 0) {
//         perror("setsockopt() failed");
//         close(_socket);
//         exit(84);
//     }
// }

// void Socket::initSocket(void)
// {
//     _socket = socket(AF_INET, SOCK_STREAM, 0);

//     if (_socket == -1) {
//         perror("socket() failed");
//         exit(84);
//     }
// }

// void Socket::setPort(int port)
// {
//     _port = port;
// }

// int Socket::getPort() const noexcept
// {
//     return (_port);
// }

// void Socket::setSocket(int socket)
// {
//     _socket = socket;
// }

// int Socket::getSocket() const noexcept
// {
//     return (_socket);
// }

// sockaddr_in &Socket::getAddr() noexcept
// {
//     return (_addr);
// }


