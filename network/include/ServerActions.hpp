/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Actions.hpp
*/

#ifndef SERVER_ACTIONS_HPP_
#define SERVER_ACTIONS_HPP_

#include <iostream>
#include <memory>

#include "ServerClient.hpp"

class ServerActions
{
	public:
		ServerActions();
		~ServerActions();

		bool InitConnection(std::unique_ptr<ServerClient>);

	protected:
	private:
};

#endif /* !SERVER_ACTIONS_HPP_ */
