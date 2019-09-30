/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Database.hpp
*/

#ifndef DATABASE_HPP_
#define DATABASE_HPP_

#include <string>
#include <sqlite3.h>

class Database {
	public:
		Database();
		~Database();

	protected:
	private:
        sqlite3 *db;
};

#endif /* !DATABASE_HPP_ */