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

bool ServerActions::initConnection(std::unique_ptr<ServerClient> client)//, std::unique_ptr<ServerClient> client_list)
{
    std::cout << "Connecting..." << std::endl;

    client->_sock.send("call");
}

bool ServerActions::closeConnection(std::unique_ptr<ServerClient> client)
{
    std::cout << "Closing connection..." << std::endl;
}

bool ServerActions::getInfos(std::unique_ptr<ServerClient> client)
{
    std::cout << "Getting infos..." << std::endl;
}