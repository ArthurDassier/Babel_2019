/*
** EPITECH PROJECT, 2019
** Babel
** File description:
** Babel_server
*/

#include "Server.hpp"

int main(__attribute__((unused)) int argc, char **argv)
{
    Server test(std::stoi(argv[1]));

    test.Run();
}

//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

// int main()
// {
//     try
//     {
//         boost::asio::io_service io_service;
//         tcp_server server1(io_service);
//         udp_server server2(io_service);
//         io_service.run();
//     }
//     catch (std::exception &e)
//     {
//         std::cerr << e.what() << std::endl;
//     }

//     return 0;
// }