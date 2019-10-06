/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Actions.cpp
*/

#include "ServerActions.hpp"

ServerActions::ServerActions()
{
}

ServerActions::~ServerActions()
{
}

bool ServerActions::InitConnection(std::unique_ptr<ServerClient> client)//, std::unique_ptr<ServerClient> client_list)
{
    std::cout << "Connecting..." << std::endl;

    client->_sock.send("call");
}