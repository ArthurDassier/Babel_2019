/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Data.hpp
*/

#ifndef DATA_HPP_
#define DATA_HPP_

#include <ctime>
#include <sstream>
#include <string>
#include <vector>

namespace db
{
    class Data {
        public:
            typedef unsigned int ID;

            Data(const std::string &);
            Data(const std::string &, const std::string &);
            Data(const std::string &, const time_t &);
            Data(const std::string &, const std::string &, const time_t &);
            ~Data();

            ID getID() const noexcept;

            void setName(const std::string &);
            std::string getName() const noexcept;

            void setLastModifiedDate(const time_t &);
            time_t getLastModifiedDate() const noexcept;

            std::string getDataType() const noexcept;
            std::string getInfos() const noexcept;

            virtual std::string getInsertionQuery() const noexcept = 0;
            virtual std::vector<std::string> getAttributes() const noexcept = 0;
            virtual std::string getFormattedAttributes() const noexcept = 0;

        private:
            ID _id;
            std::string _name;
            time_t _lastModifiedDate;
            const std::string _dataType;
    };
}; // namespace db

#endif /* !DATA_HPP_ */
