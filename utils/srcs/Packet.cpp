/*
** EPITECH PROJECT, 2019
** IndieStudio_2018
** File description:
** Packet.cpp
*/

#include "Packet.hpp"

std::string const utils::Packet::getPacket() noexcept
{
    std::ostringstream buf;
    boost::property_tree::write_json(buf, root);
    return buf.str();
}

void utils::Packet::setType(const std::string type)
{
    root.put("type", type);
}

std::vector<std::array<float, 2>> utils::Packet::getVector() const noexcept
{
    return v;
}

std::size_t utils::Packet::getVectorSize() const noexcept
{
    return v.size();
}

void utils::Packet::clear()
{
    root.clear();
}