/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Server
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <ctime>
#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <thread>

using boost::asio::ip::udp;

enum messageType {
    WELCOME = 0,
    INFO = 1,
    UNKNOW = 2
};

namespace network {
    class Server
    {
        public:
            Server(boost::asio::io_context& io_context, short port);
            ~Server() = default;

        private:
            void check_clock(std::list<std::tuple<udp::endpoint, int, std::clock_t> >& _list);
            void start_receive();
            void handle_receive(const boost::system::error_code& error,
                std::size_t buff_size);
            void handle_send(boost::shared_ptr<std::string>,
                const boost::system::error_code&,
                std::size_t);
            void find_command(std::string data, std::size_t buff_size, int currentClient);
            void sender_message(messageType message_type, int currentClient);
            void call_fct(int currentClient, int clientAsk);

            std::list<std::tuple<udp::endpoint, int, std::clock_t> > _list_client;
            boost::array<char, 1024> _recv_buffer;
            udp::endpoint   _remote_endpoint;
            udp::socket     _socket;
            std::thread     _thread_check;
            int             _clientNb;
    };
}; // namespace network