/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Database.cpp
*/

#include "Database.hpp"

Database::Database(const std::string database)
{
    int rc = sqlite3_open(database, &db);
    if (rc) {
        // Can't open database"
    } else {
        // Opened database successfully
    }
}

Database::~Database()
{
    sqlite3_close(db);
}
