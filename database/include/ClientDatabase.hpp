/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** ClientDatabse.hpp
*/

#pragma once

#include <arpa/inet.h>
#include <netinet/in.h>

#include "Data.hpp"

namespace db
{
    using IP = std::string;

    class ClientDatabase : public Data
    {
        public:
            ClientDatabase();
            ClientDatabase(const std::string &);
            ClientDatabase(const std::string &, time_t &);
            ~ClientDatabase();

            void setIPAddr(const IP &) noexcept;
            IP getIPAddr() const;

            std::string getInsertionQuery() const noexcept;

            std::vector<std::string> getAttributes() const noexcept;
            std::string getFormattedAttributes() const noexcept;
            std::string getFormattedValues() const noexcept;

        private:
            std::string getStringInfos() const noexcept;

            IP _ipAddr;
            std::vector<std::string> _attributes = {
                "ID",
                "NAME",
                "DATE"
            };
    };
}; // namespace db