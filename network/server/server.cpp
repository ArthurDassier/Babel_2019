/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Babel_server
*/

#include "Server.hpp"

int main(__attribute__((unused)) int argc, char **argv)
{
    ns::Server test(std::stoi(argv[1]));

    test.Run();
    return 0;
}