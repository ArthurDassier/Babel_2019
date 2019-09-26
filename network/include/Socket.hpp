#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define DEFAULT_PORT 0

const int MAX_CONNECTIONS = 5;
const int MAX_RECV = 1024;

using sockaddr_in = struct sockaddr_in;
using sockaddr = struct sockaddr;

class Socket
{
    public:
        Socket();
        ~Socket() = default;

        bool create();
        bool create_listening_TCP(const int);
        bool bind(const int, uint32_t, uint32_t);
        bool listen() const;
        bool accept(Socket &) const;

        bool connect(const std::string, const int);

        bool send(const std::string) const;
        int read(std::string &) const;
        int recv(std::string &) const;

        // void set_non_blocking(const bool);
        bool is_valid() const;
    
        int _sock;
        sockaddr_in _addr;
    private:
};
