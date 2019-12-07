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
#include <ctime>

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
            _thread_check = std::thread(&udp_server::check_clock, this, std::ref(_list_client));
            start_receive();
        }

    private:

        void check_clock(std::list<std::tuple<udp::endpoint, int, std::clock_t> >& _list)
        {
            while (1) {
                usleep(1000000); //modifier lui pour plus de précisions
                for (auto const& i : _list) {
                    std::clock_t c_end = std::clock();
                    // std::cout << std::get<2>(i) << " and " << c_end << std::endl;
                    int result = (c_end-std::get<2>(i)) / 100;
                    // std::cout << "le temps: " << result << std::endl;
                    if (result >= 5) {
                        std::cout << "deco du client" << std::get<1>(i) << std::endl;
                        _list.remove(std::make_tuple(std::get<0>(i), std::get<1>(i), std::get<2>(i)));
                        break;
                    }
                }
            }
        }

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
                    if (std::get<0>(i) == _remote_endpoint) {
                        std::cout << "il existe deja" << std::endl;
                        *(std::clock_t *)&std::get<2>(i) = std::clock();
                        isExist = true;
                        break;
                    }
                }
                if (isExist == false) {
                    std::clock_t c_start = std::clock();
                    _list_client.push_back(std::make_tuple(_remote_endpoint, _clientNb, c_start));
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
        std::list<std::tuple<udp::endpoint, int, std::clock_t> > _list_client;
        std::thread _thread_check;
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
