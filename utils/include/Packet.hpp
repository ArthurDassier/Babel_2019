/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Packet.hpp
*/

#pragma once

#include <array>
#include <ostream>
#include <sstream>
#include <vector>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace utils
{
    using pt = boost::property_tree::ptree;

    class Packet
    {
        public:
            Packet() = default;
            ~Packet() = default;

            std::string const getPacket() noexcept;

            void setType(const std::string);

            template <typename T>
            void addData(const std::string name, const T data)
            {
                root.put(name, data);
            }

            template <typename T>
            void addToVector(const T data)
            {
                v.push_back(data);
            }
            std::vector<std::array<float, 2>> getVector() const noexcept;
            std::size_t getVectorSize() const noexcept;

            template <typename T>
            void addPairToList(const std::string name1, const std::string name2, T elem1, T elem2)
            {
                pt f;
                pt s;

                f.put(name1, elem1);
                f.put(name2, elem2);

                list.push_back(std::make_pair("", f));
            }

            template <typename T>
            void addDataToList(const std::string name, const T data)
            {
                list.put(name, data);
            }

            template <typename T>
            void addList(const std::string name, std::vector<T> data)
            {
                pt matrix_node;

                for (auto &it : data) {
                    pt row;
                    for (auto &it_c : it) {
                        pt cell;
                        cell.put_value(it_c);
                        row.push_back(std::make_pair("", cell));
                    }
                    matrix_node.push_back(std::make_pair("", row));
                }
                root.add_child(name, matrix_node);
                v.clear();
            }

            void clear();

        private:
            pt root;
            pt list;
            std::vector<std::array<float, 2>> v;
    };
}; // namespace utils