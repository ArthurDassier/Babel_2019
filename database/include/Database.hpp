/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Database.hpp
*/

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <sqlite3.h>
#include <unordered_map>

#include "ClientDatabase.hpp"

namespace db
{
	using Record = std::vector<std::string>;
	using Records = std::vector<Record>;

	class Database
	{
		public:
			Database(const std::string &);
			~Database();

			inline sqlite3 *getHandle() const noexcept
			{
				return db;
			}

			void setDB(sqlite3* ptr)
			{
				db = ptr;
			}

			bool connect(const std::string &);
			bool createTable(const std::string &);
			bool insertData(std::unique_ptr<Data>);
			bool getData(const std::string &, const std::vector<std::string> & = {0});
			bool upsertData(const std::string &, const std::string &);
			bool deleteData(const std::string &, const std::string &);

		private:
			int sqlStmt(const std::string &);
			Records selectStmt(const std::string &);
			static int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names);

			sqlite3 *db;
	};
}; // namespace db