/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ClientDatabase.cpp
*/

#include "ClientDatabase.hpp"

db::ClientDatabase::ClientDatabase():
    Data("CLIENT")
{
}

db::ClientDatabase::ClientDatabase(const std::string &name):
    Data("CLIENT", name)
{
}

db::ClientDatabase::ClientDatabase(const time_t &lastModifiedDate):
    Data("CLIENT", lastModifiedDate)
{
}

db::ClientDatabase::ClientDatabase(const std::string &name, const time_t &lastModifiedDate):
    Data("CLIENT", name, lastModifiedDate)
{
}

db::ClientDatabase::~ClientDatabase()
{
}

void db::ClientDatabase::setIPAddr(const IP &ipAddr) noexcept
{
    _ipAddr = ipAddr;
}

db::IP db::ClientDatabase::getIPAddr() const
{
    return _ipAddr;
}

std::string db::ClientDatabase::getInsertionQuery() const noexcept
{
    std::string sql;
    std::ostringstream oss;

    oss << "INSERT INTO " << Data::getDataType();
    oss << getFormattedAttributes();
    oss << getFormattedValues();

    return oss.str();
}

std::vector<std::string> db::ClientDatabase::getAttributes() const noexcept
{
    return _attributes;
}

std::string db::ClientDatabase::getFormattedAttributes() const noexcept
{
    std::ostringstream oss;
    int end = 0;

    oss << " (";
    for (auto &it : getAttributes()) {
        end = it.compare(getAttributes().back());
        oss << it << (end != 0 ? "," : "");
    }
    oss << ") ";
    return oss.str();
}

std::string db::ClientDatabase::getFormattedValues() const noexcept
{
    std::ostringstream oss;
    int end = 0;

    oss << "VALUES (";
    for (auto &it : getAttributes()) {
        end = it.compare(getAttributes().back());
        if (it.compare("ID") == 0)
            oss << getID();
        else if (it.compare("NAME") == 0)
            oss << "'" << getName() << "'";
        else if (it.compare("DATE") == 0)
            oss << getLastModifiedDate();
        else
            exit(0);
        oss << (end != 0 ? "," : ");");
    }
    return oss.str();
}

std::string db::ClientDatabase::getStringInfos() const noexcept
{
}