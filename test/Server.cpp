/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Server.cpp
*/

#include "Server.hpp"

Server::Server()
{
}

Server::~Server()
{
}

void Server::Connection()
{
    for (;;) {
        sockaddr_in from = {0};
        socklen_t addrlen = sizeof(from);
        SOCKET newClient = accept(server, (sockaddr *)(&from), &addrlen);
        if (newClient != INVALID_SOCKET) {
            std::thread([newClient, from]() {
                const std::string clientAddress = inet_ntoa(); //Sockets::GetAddress(from);
                const unsigned short clientPort = ntohs(from.sin_port);
                std::cout << "Connexion de " << clientAddress.c_str() << ":" << clientPort << std::endl;
                bool connected = true;
                for (;;)
                {
                    char buffer[200] = {0};
                    int ret = recv(newClient, buffer, 199, 0);
                    if (ret == 0 || ret == SOCKET_ERROR)
                        break;
                    std::cout << "[" << clientAddress << ":" << clientPort << "]" << buffer << std::endl;
                    ret = send(newClient, buffer, ret, 0);
                    if (ret == 0 || ret == SOCKET_ERROR)
                        break;
                }
                std::cout << "Deconnexion de [" << clientAddress << ":" << clientPort << "]" << std::endl;
            }).detach();
        }
    }
}