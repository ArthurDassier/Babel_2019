#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>

#include "Server.hpp"

int main(int argc, char **argv)
{
    try
    {
        boost::asio::io_context io_context;
        network::Server server(io_context, std::atoi(argv[1]));
        io_context.run();
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}