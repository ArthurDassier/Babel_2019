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

db::Data::Data(const std::string &dataType, const time_t &lastModifiedDate):
    _dataType(dataType),
    _id(0),
    _name(nullptr),
    _lastModifiedDate(lastModifiedDate)
{
}

db::Data::Data(const std::string &dataType, const std::string &name, const time_t &lastModifiedDate):
    _dataType(dataType),
    _id(0),
    _name(name),
    _lastModifiedDate(lastModifiedDate)
{
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

void db::Data::setLastModifiedDate(const time_t &lastModifiedDate)
{
    _lastModifiedDate = lastModifiedDate;
}

time_t db::Data::getLastModifiedDate() const noexcept
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
    std::string lastModifiedDate = "LastModifiedDate: " + std::to_string(getLastModifiedDate()) + ", ";

    return type + id + name + lastModifiedDate;
}