/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Data.cpp
*/

#include "Data.hpp"

db::Data::Data(const std::string &dataType):
    _dataType(dataType),
    _id(0),
    _name(nullptr),
    _lastModifiedDate(0)
{   
}

db::Data::Data(const std::string &dataType, const std::string &name):
    _dataType(dataType),
    _id(0),
    _name(name),
    _lastModifiedDate(0)
{
}

db::Data::Data(const std::string &dataType, time_t &lastModifiedDate):
    _dataType(dataType),
    _id(0),
    _name(nullptr)
{
    setLastModifiedDate(lastModifiedDate);
}

db::Data::Data(const std::string &dataType, const std::string &name, time_t &lastModifiedDate):
    _dataType(dataType),
    _id(0),
    _name(name)   
{
    setLastModifiedDate(lastModifiedDate);
}

db::Data::~Data()
{
}

db::Data::ID db::Data::getID() const noexcept
{
    return _id;
}

void db::Data::setName(const std::string &name)
{
    _name = name;
}

std::string db::Data::getName() const noexcept
{
    return _name;
}

void db::Data::setLastModifiedDate(time_t &lastModifiedDate)
{
    struct tm *timeinfo;
    char buffer[80];

    time(&lastModifiedDate);
    timeinfo = localtime(&lastModifiedDate);
    strftime(buffer, sizeof(buffer), "%d%m%Y-%H:%M:%S", timeinfo);
    _lastModifiedDate = std::string(buffer);
}

std::string db::Data::getLastModifiedDate() const noexcept
{
    return _lastModifiedDate;
}

std::string db::Data::getDataType() const noexcept
{
    return _dataType;
}

std::string db::Data::getInfos() const noexcept
{
    std::string type = "Type: " + getDataType() + ", ";
    std::string id = "ID: " + std::to_string(getID()) + ", ";
    std::string name = "Name: " + getName() + ", ";
    std::string lastModifiedDate = "LastModifiedDate: " + getLastModifiedDate() + ", ";

    return type + id + name + lastModifiedDate;
}