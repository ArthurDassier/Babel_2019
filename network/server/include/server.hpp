/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** udp boost server
*/

#pragma once

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

enum messageType {
    WELCOME = 0,
    INFO = 1,
    UNKNOW = 2
};


class udp_server
{
    public:
        udp_server(boost::asio::io_context& io_context, short port);

    private:

        void check_clock(std::list<std::tuple<udp::endpoint, int, std::clock_t> >& _list);
        void start_receive();
        void handle_receive(const boost::system::error_code& error,
            std::size_t buff_size);
        void handle_send(boost::shared_ptr<std::string> /*message*/,
            const boost::system::error_code& /*error*/,
            std::size_t /*bytes_transferred*/);
        void find_command(std::string data, std::size_t buff_size, int currentClient);
        void sender_message(messageType message_type, int currentClient);
        void call_fct();

        udp::socket _socket;
        udp::endpoint _remote_endpoint;
        boost::array<char, 1024> _recv_buffer;
        std::list<std::tuple<udp::endpoint, int, std::clock_t> > _list_client;
        std::thread _thread_check;
        int _clientNb;
};