#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <list>
#include <thread>
#include <mutex>

using boost::asio::ip::tcp;

class session : public std::enable_shared_from_this<session>
{
    public:
        session(tcp::socket socket)
            : _socket(std::move(socket)),
              _isCall(false),
              _isDeco(false)
        {
        }

        void start()
        {
            do_read();
        }

        bool wantToCall()
        {
            return _isCall;
        }

        bool wantToDeco()
        {
            return _isDeco;
        }

    private:
        void do_read()
        {
            auto self(shared_from_this());
            _socket.async_read_some(boost::asio::buffer(_data, max_length),
                [this, self](boost::system::error_code ec, std::size_t length)
                {
                if (!ec)
                {
                    // std::cout << "taille :" << length << " data :" << _data;
                    char str[5] = "call";
                    int i = 0;
                    while (i < length) {
                        if (str[i] == _data[i])
                            i++;
                        else
                            break;
                    }
                    if (i == 4)
                        call_fct();
                    do_write(length);
                } 
                else
                {
                    // std::cout << "deco de : " << _socket.remote_endpoint().address().to_string() << std::endl;
                    _isDeco = true;
                }
                });
        }

        void do_write(std::size_t length)
        {
            auto self(shared_from_this());
            boost::asio::async_write(_socket, boost::asio::buffer(_data, length),
                [this, self](boost::system::error_code ec, std::size_t /*length*/)
                {
                if (!ec)
                {
                    do_read();
                }
                });
        }

        void call_fct()
        {
            std::cout << "wow ya un call la" << std::endl;
            _isCall = true;
        }

        tcp::socket _socket;
        enum { max_length = 1024 };
        char _data[max_length];
        bool _isCall;
        bool _isDeco;
};

class tcp_server
{
    public:
        tcp_server(boost::asio::io_service& io_service, short port)
            : _acceptor(io_service, tcp::endpoint(tcp::v4(), port)),
            _socket(io_service),
            _clientNb(1)
        {

            _thread_check = std::thread(&tcp_server::check_session, this, std::ref(_list_session));
            do_accept();
        }

    private:

        void check_session(std::list<std::pair<std::shared_ptr<session>, int> >& _list)
        {
            while (1) {
                usleep(1000000);
                for (auto const& i : _list) {
                    if (i.first->wantToDeco() == true) {
                        std::cout << "session qui deco: " << i.second << std::endl;
                         _list.remove(std::make_pair(i.first, i.second));
                         break;
                    } else {
                        if (i.first->wantToCall() == true)
                            std::cout << "session qui call: " << i.second << std::endl;
                    }
                }
            }
        }

        void do_accept()
        {
            _acceptor.async_accept(_socket,
                [this](boost::system::error_code ec)
                {
                if (!ec)
                {
                    std::string s = _socket.remote_endpoint().address().to_string(); //a faire avant sinon crash -> perd la socket
                    std::cout << "new session created, client" << _clientNb << ": " << s << std::endl;
                    // std::make_shared<session>(std::move(_socket))->start();
                    std::shared_ptr<session> new_session = std::make_shared<session>(std::move(_socket));
                    _list_session.push_back(std::make_pair(new_session, _clientNb));
                    new_session->start();
                    _clientNb++;
                }
                do_accept();
                });
        }

        tcp::acceptor _acceptor;
        tcp::socket _socket;
        std::list<std::pair<std::shared_ptr<session>, int> > _list_session;
        std::thread _thread_check;
        int _clientNb;
};

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2) {
            std::cerr << "Usage: async_tcp_echo_server <port>" << std::endl;
            return 84;
        }
        boost::asio::io_service io_service;
        tcp_server s(io_service, std::atoi(argv[1]));

        io_service.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}