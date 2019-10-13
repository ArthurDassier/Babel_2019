/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ServerClient.hpp
*/

#pragma once

#include "Socket.hpp"
#include "TCPSocket.hpp"

/*! \class ServerClient
* \brief Class representing the ServerClient
*
*  This class handle the server's clients
*/

class ServerClient
{
    public:
        ServerClient(Socket sock);
        ~ServerClient() = default;

        std::string getUsername() const noexcept;
        Socket _sock;

    private:
        std::string _username;
};    