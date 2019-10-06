/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ServerClient.hpp
*/

#ifndef SERVERCLIENT_HPP_
#define SERVERCLIENT_HPP_

#include "Socket.hpp"

class ServerClient
{
    public:
        ServerClient(Socket sock) : _sock(sock)
        // _TCP_sock(sock)
        {
            std::cout << "Client add with fd n°" << sock._sock << std::endl;
        }
        Socket _sock;
        // TCPSocket _TCP_sock;

    private:
        // static void *PrintHello(void *threadid)
        // {
        //     long tid;
        //     tid = (long)threadid;
        //     std::cout << "Hello World! Thread ID, " << tid << std::endl;
        //     pthread_exit(NULL);
        // }

        // pthread_t thread;
        // UDPSocket _UDP_sock;
    };

#endif /* !SERVERCLIENT_HPP_ */
