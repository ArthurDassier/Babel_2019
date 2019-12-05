// #include <iostream>
// #include <boost/array.hpp>
// #include <boost/asio.hpp>

// using boost::asio::ip::udp;

// class UDPClient
// {
// public:
//     UDPClient(
//         boost::asio::io_service& io_service, 
//         const std::string& host, 
//         const std::string& port
//     ) : io_service_(io_service), socket_(io_service, udp::endpoint(udp::v4(), 0)) {
//         udp::resolver resolver(io_service_);
//         udp::resolver::query query(udp::v4(), host, port);
//         udp::resolver::iterator iter = resolver.resolve(query);
//         endpoint_ = *iter;
//     }

//     ~UDPClient()
//     {
//         socket_.close();
//     }

//     void send(const std::string& msg) {
//         socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_);
//     }

//     // void receive()
//     // {
//     //     while (1) {
//     //         socket_.receive_from
//     //     }
//     // }

// private:
//     boost::asio::io_service& io_service_;
//     udp::socket socket_;
//     udp::endpoint endpoint_;
// };

// int main(int argc, char **argv)
// {
//     boost::asio::io_service io_service;
//     UDPClient client(io_service, "localhost", argv[1]);

//     while (1) {
//         std::string str;
//         std::getline(std::cin, str);
//         client.send(str);
//     }
// }


#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main()
{
    try
    {
        boost::asio::io_service io_service;

        udp::endpoint receiver_endpoint (boost::asio::ip::address::from_string("127.0.0.1"), 4242);
        
        udp::socket socket(io_service); // (1)
        socket.open(udp::v4());

        while (1) {
            // boost::array<char, 6> send_buf  = { 'H', 'e', 'l', 'l', 'o' }; // (2)
            std::string str;
            std::getline(std::cin, str);
            socket.send_to(boost::asio::buffer(str), receiver_endpoint); // (3)

            boost::array<char, 128> recv_buf; // (4)
            udp::endpoint sender_endpoint;
            size_t len = socket.receive_from(boost::asio::buffer(recv_buf), sender_endpoint); // (5)

            std::cout.write(recv_buf.data(), len); // (6)
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}