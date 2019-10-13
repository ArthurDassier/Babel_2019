/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ClientDatabase.cpp
*/

#include "ClientDatabase.hpp"

/*!
 * \fn db::ClientDatabase::ClientDatabase()
 * \brief ?
 *
 * \param void
 */

db::ClientDatabase::ClientDatabase():
    Data("CLIENT")
{
}

/*!
 * \fn db::ClientDatabase::ClientDatabase(const std::string &name)
 * \brief ?
 *
 * \param const std::string &name
 */


db::ClientDatabase::ClientDatabase(const std::string &name):
    Data("CLIENT", name)
{
}

/*!
 * \fn db::ClientDatabase::ClientDatabase(const std::string &name, time_t &lastModifiedDate)
 * \brief ?
 *
 * \param const std::string &name, time_t &lastModifiedDate
 */


db::ClientDatabase::ClientDatabase(const std::string &name, time_t &lastModifiedDate):
    Data("CLIENT", name, lastModifiedDate)
{
}

/*!
 * \fn db::ClientDatabase::~ClientDatabase()
 * \brief ?
 *
 * \param void
 */


db::ClientDatabase::~ClientDatabase()
{
}

/*!
 * \fn db::ClientDatabase::setIPAddr(const IP &ipAddr) noexcept
 * \brief ?
 *
 * \param const IP &ipAddr
 */


void db::ClientDatabase::setIPAddr(const IP &ipAddr) noexcept
{
    _ipAddr = ipAddr;
}

/*!
 * \fn db::ClientDatabase::getIPAddr() const
 * \brief ?
 *
 * \param void
 */


db::IP db::ClientDatabase::getIPAddr() const
{
    return _ipAddr;
}

/*!
 * \fn db::ClientDatabase::getInsertionQuery() const noexcept
 * \brief ?
 *
 * \param void
 */


std::string db::ClientDatabase::getInsertionQuery() const noexcept
{
    std::string sql;
    std::ostringstream oss;

    oss << "INSERT INTO " << Data::getDataType();
    oss << getFormattedAttributes();
    oss << getFormattedValues();

    return oss.str();
}

/*!
 * \fn db::ClientDatabase::ClientDatabase::getAttributes() const noexcept
 * \brief ?
 *
 * \param void
 */


std::vector<std::string> db::ClientDatabase::getAttributes() const noexcept
{
    return _attributes;
}

/*!
 * \fn db::ClientDatabase::getFormattedAttributes() const noexcept
 * \brief ?
 *
 * \param void
 */


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

/*!
 * \fn db::ClientDatabase::getFormattedValues() const noexcept
 * \brief ?
 *
 * \param void
 */


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
            oss << "'" << getLastModifiedDate() << "'";
        else
            exit(0);
        oss << (end != 0 ? "," : ");");
    }
    return oss.str();
}

/*!
 * \fn db::ClientDatabase::getStringInfos() const noexcept
 * \brief ?
 *
 * \param void
 */


std::string db::ClientDatabase::getStringInfos() const noexcept
{
}