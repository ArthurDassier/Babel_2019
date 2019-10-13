/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ServerClient.cpp
*/

#include "ServerClient.hpp"

ServerClient::ServerClient(Socket sock)
    : _sock(sock)
{
}

std::string ServerClient::getUsername() const noexcept
{
    return _username;
}