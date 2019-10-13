/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Actions.hpp
*/

#pragma once

#include <iostream>
#include <memory>

#include "ServerClient.hpp"

/*! \class ServerActions
* \brief Class representing the ServerActions
*
*  This class handle the server's actions
*/

class ServerActions
{
	public:
		ServerActions();
		~ServerActions();

		bool initConnection(std::unique_ptr<ServerClient>);
		bool closeConnection(std::unique_ptr<ServerClient>);
		bool getInfos(std::unique_ptr<ServerClient>);
};