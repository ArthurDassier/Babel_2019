/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Server.hpp
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <arpa/inet.h>
#include <iostream>
// #include <deque>
// #include <memory>
#include <sys/socket.h>
#include <thread>

#define INVALID_SOCKET (-1)

using SOCKET = int;

class Server {
	public:
		Server();
		~Server();

        void Connection();

    private:
};

#endif /* !SERVER_HPP_ */