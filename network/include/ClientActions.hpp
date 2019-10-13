/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ClientActions.hpp
*/

#pragma once

#include <iostream>

/*! \class ClientActions
* \brief Class representing the ClientActions
*
*  This class handle the ClientActions
*/

class ClientActions
{
	public:
		ClientActions();
		~ClientActions();

        struct info_s {
            std::string ip;
            unsigned short port;
            std::string name;
        };

        bool sendInfos(const info_s &);

    protected:
	private:
};