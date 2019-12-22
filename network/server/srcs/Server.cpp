/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Server
*/

#include "Server.hpp"

std::string make_daytime_string()
{
    std::time_t now = std::time(0);
    return std::ctime(&now);
}

network::Server::Server(boost::asio::io_context& io_context, short port)
    : _socket(io_context, udp::endpoint(udp::v4(), port)),
    _clientNb(1)
{
    _thread_check = std::thread(&network::Server::check_clock, this, std::ref(_list_client));
    start_receive();
}

void network::Server::check_clock(std::list<std::tuple<udp::endpoint, int, std::clock_t> >& _list)
{
    while (1) {
        usleep(1000000);
        for (auto const& i : _list) {
            std::clock_t c_end = std::clock();
            int result = (c_end-std::get<2>(i)) / 100;
            if (result >= 30) {
                std::cout << "Disconnection of client" << std::get<1>(i) << std::endl;
                _list.remove(std::make_tuple(std::get<0>(i), std::get<1>(i), std::get<2>(i)));
                break;
            }
        }
    }
}

void network::Server::start_receive()
{
    _socket.async_receive_from(
        boost::asio::buffer(_recv_buffer), _remote_endpoint,
        boost::bind(&network::Server::handle_receive, this,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void network::Server::handle_receive(const boost::system::error_code& error,
    std::size_t buff_size)
{
    if (!error) {
        boost::shared_ptr<std::string> message(
        new std::string(make_daytime_string()));

        bool isExist = false;
        std::string data(_recv_buffer.begin(), buff_size);
        std::cout << "Message from " << _remote_endpoint << ": " << data << std::endl;
        for (auto const& i : _list_client) {
            if (std::get<0>(i) == _remote_endpoint) {
                std::cout << "Client already exists" << std::endl;
                *(std::clock_t *)&std::get<2>(i) = std::clock();
                find_command(data, buff_size, std::get<1>(i));
                isExist = true;
                break;
            }
        }
        if (isExist == false) {
            std::clock_t c_start = std::clock();
            _list_client.push_back(std::make_tuple(_remote_endpoint, _clientNb, c_start));
            sender_message(WELCOME, _clientNb);
            _clientNb++;
            std::cout << "Client doesn't exist" << std::endl;
            start_receive();
        }
        start_receive();
    }
}

void network::Server::handle_send(boost::shared_ptr<std::string> /*message*/,
    const boost::system::error_code& /*error*/,
    std::size_t /*bytes_transferred*/)
{
}

void network::Server::find_command(std::string data, std::size_t buff_size, int currentClient)
{
    std::string command = data.substr(0, data.find('-'));
    std::string clientNbAsk = data.substr(data.find('-') + 1);

    if (command.compare("call") == 0)
        call_fct(currentClient, std::atoi(clientNbAsk.c_str()));
    else if (command.compare("info") == 0)
        sender_message(INFO, currentClient);
    else
        sender_message(UNKNOW, currentClient);
}

void network::Server::sender_message(messageType message_type, int currentClient)
{
    std::string w_message;
    if (message_type == WELCOME)
        w_message += "Welcome, you're the client " + std::to_string(currentClient) + "\n";
    else if (message_type == INFO)
        w_message += "As you have asked client " + std::to_string(currentClient) + "\n";
    else if (message_type == UNKNOW)
        w_message += "Your command is unknow.\n";

    if (message_type == WELCOME || message_type == INFO) {
        w_message += "Here you can see the list of client connected:\n";
        for (auto const& i : _list_client) {
            std::stringstream ss;
            ss << std::get<0>(i);
            std::string str = ss.str();
            w_message += "-client " + std::to_string(std::get<1>(i)) + " on " + str + "\n";
        }
    }

    if (message_type == INFO || message_type == UNKNOW)
        w_message += "Here you can see the list of commands:\n-info = get information about clients connected\n-call-\"client nb\" = call the client depends on the number given\n";

    boost::shared_ptr<std::string> message(new std::string(w_message));
    _socket.async_send_to(boost::asio::buffer(*message), _remote_endpoint,
        boost::bind(&network::Server::handle_send, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}

void network::Server::call_fct(int currentClient, int clientAsk)
{
    std::string tmp;
    for (auto const& i : _list_client) {
        if (std::get<1>(i) == clientAsk) {
            tmp += std::get<0>(i).address().to_string() + ":" + std::to_string(std::get<0>(i).port());
            boost::shared_ptr<std::string> message(new std::string(tmp));
                _socket.async_send_to(boost::asio::buffer(*message), _remote_endpoint,
                boost::bind(&network::Server::handle_send, this, message,
                boost::asio::placeholders::error,
                boost::asio::placeholders::bytes_transferred));
                return;
        }
    }
    tmp += "The client whose you want to call doesn't exist.\n";
    boost::shared_ptr<std::string> message(new std::string(tmp));
    _socket.async_send_to(boost::asio::buffer(*message), _remote_endpoint,
        boost::bind(&network::Server::handle_send, this, message,
        boost::asio::placeholders::error,
        boost::asio::placeholders::bytes_transferred));
}