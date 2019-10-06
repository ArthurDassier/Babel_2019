/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** databse.cpp
*/

#include "Database.hpp"

#include <cstddef>

int main()
{
    Database db("client_database.db");
    auto client = std::make_unique<ClientDatabase>("Laura");

    std::cout << client->getInfos() << std::endl;
    db.createTable("CLIENT("
                   "ID INT PRIMARY KEY     NOT NULL,"
                   "NAME           TEXT    NOT NULL,"
                   "DATE           TEXT)");
    if (db.insertData(std::move(client)) != 0) {
        return 1;
    }
    db.upsertData("CLIENT", "NAME = 'Theo' where ID=1");
    db.getData("CLIENT", {"Name", "ID"});
    db.deleteData("CLIENT", "ID=0");
    db.getData("CLIENT", {"Name", "ID"});
    return 0;
}