#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <list>
#include <thread>
#include <mutex>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
    using namespace std; // For time_t, time and ctime;
    time_t now = time(0);
    return ctime(&now);
}

class udp_server
{
    public:
        udp_server(boost::asio::io_context& io_context, short port)
            : _socket(io_context, udp::endpoint(udp::v4(), port)),
            _clientNb(1)
        {
            start_receive();
        }

    private:
    void start_receive()
    {
        _socket.async_receive_from(
            boost::asio::buffer(_recv_buffer), _remote_endpoint,
            boost::bind(&udp_server::handle_receive, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }

    void handle_receive(const boost::system::error_code& error,
        std::size_t buff_size)
    {
        if (!error) {
            boost::shared_ptr<std::string> message(
            new std::string(make_daytime_string()));

            bool isExist = false;
            std::string data(_recv_buffer.begin(), buff_size);
            std::cout << "Message de " << _remote_endpoint << ": " << data << std::endl;
            for (auto const& i : _list_client) {
                if (i.first == _remote_endpoint) {
                    std::cout << "il existe deja" << std::endl;
                    isExist = true;
                    break;
                }
            }
            if (isExist == false) {
                _list_client.push_back(std::make_pair(_remote_endpoint, _clientNb));
                _clientNb++;
                std::cout << "il existe pas" << std::endl;
            }
            _socket.async_send_to(boost::asio::buffer(*message), _remote_endpoint,
            boost::bind(&udp_server::handle_send, this, message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));

        start_receive();
        }
    }

    void handle_send(boost::shared_ptr<std::string> /*message*/,
        const boost::system::error_code& /*error*/,
        std::size_t /*bytes_transferred*/)
    {
    }

    udp::socket _socket;
    udp::endpoint _remote_endpoint;
    boost::array<char, 1024> _recv_buffer;
    std::list<std::pair<udp::endpoint, int> > _list_client;
    int _clientNb;
};

int main(int argc, char **argv)
{
  try
  {
    boost::asio::io_context io_context;
    udp_server server(io_context, std::atoi(argv[1]));
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
