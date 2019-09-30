/*
** EPITECH PROJECT, 2019
** Server_CPP
** File description:
** Server
*/

#pragma once

#include <algorithm>
#include <arpa/inet.h>
#include <deque>
#include <memory>
#include <pthread.h>
#include <sys/socket.h>
// #include <thread>

#include "Socket.hpp"
#include "TCPSocket.hpp"
#include "UDPSocket.hpp"

#define DEFAULT_PORT 0

using sockaddr_in = struct sockaddr_in;
using socket_t = int;

class Client
{
    public:
        Client(Socket sock):
            _sock(sock)
            // _TCP_sock(sock) 
        {
            std::cout << "Client add with fd n°" << sock._sock << std::endl;
            // pthread_create(&thread, NULL, PrintHello, this);
            // pthread_t threads[5];
            // int rc;
            // int i;

            // for (i = 0; i < 5; i++)
            // {
            //     std::cout << "main() : creating thread, " << i << std::endl;
            //     rc = pthread_create(&threads[i], NULL, PrintHello, reinterpret_cast<void *>(i));

            //     if (rc)
            //     {
            //         std::cout << "Error:unable to create thread," << rc << std::endl;
            //         exit(-1);
            //     }
            // }
            // pthread_exit(NULL);
        }
        Socket _sock;
        // TCPSocket _TCP_sock;

    private:
        static void *PrintHello(void *threadid)
        {
            long tid;
            tid = (long)threadid;
            std::cout << "Hello World! Thread ID, " << tid << std::endl;
            pthread_exit(NULL);
        }

        pthread_t thread;
        // UDPSocket _UDP_sock;
};

class Server
{
	public:
		Server(const int port);
		~Server();

        void initMainSocket(const int);

        void removeClient(Client);

        void PollEvent();
        void Run();
        void shutdown();

        void HandleConnection();
        void HandleReceive(Client);
        // void solveRequest();
        void MatchCommand(std::unique_ptr<Client> client, const std::string &command);

        void Call(std::unique_ptr<Client> client);

    private:
        void add_sockets_to_set(socket_t *);

        bool _status;
        unsigned short _max_connections;
        TCPSocket _sock;

        std::deque<std::unique_ptr<Client>> _client_list;
        // Socket _listen_sock;
        // socket_t _sock;
        // sockaddr_in _addr;
        // // Socket _main_socket;
        fd_set _sock_set;
        // std::deque<std::unique_ptr<Client>> _client_list;
};

// #include <ctime>
// #include <iostream>
// #include <string>
// #include <boost/array.hpp>
// #include <boost/bind.hpp>
// #include <boost/shared_ptr.hpp>
// #include <boost/enable_shared_from_this.hpp>
// #include <boost/asio.hpp>

// using boost::asio::ip::tcp;
// using boost::asio::ip::udp;

// static std::string make_daytime_string()
// {
//     using namespace std; // For time_t, time and ctime;
//     time_t now = time(0);
//     return ctime(&now);
// }

// class session
//     : public std::enable_shared_from_this<session>
//     {
//     public:
//         session(tcp::socket socket)
//             : socket_(std::move(socket))
//         {
//         }

//         void start()
//         {
//             do_read();
//         }

//     private:
//         void do_read()
//         {
//             auto self(shared_from_this());
//             socket_.async_read_some(boost::asio::buffer(data_, max_length),
//                                     [this, self](boost::system::error_code ec, std::size_t length) {
//                                         if (!ec)
//                                         {
//                                             do_write(length);
//                                         }
//                                     });
//         }

//         void do_write(std::size_t length)
//         {
//             auto self(shared_from_this());
//             boost::asio::async_write(socket_, boost::asio::buffer(data_, length),
//                                     [this, self](boost::system::error_code ec, std::size_t /*length*/) {
//                                         if (!ec)
//                                         {
//                                             do_read();
//                                         }
//                                     });
//         }

//         tcp::socket socket_;
//         enum
//         {
//             max_length = 1024
//         };
//         char data_[max_length];
// };

// class tcp_connection
//     : public boost::enable_shared_from_this<tcp_connection>
// {
//     public:
//         typedef boost::shared_ptr<tcp_connection> pointer;

//         static pointer create(boost::asio::io_service &io_service)
//         {
//             return pointer(new tcp_connection(io_service));
//         }

//         tcp::socket &socket()
//         {
//             return socket_;
//         }

//         void start()
//         {
//             message_ = make_daytime_string();

//             boost::asio::async_write(socket_, boost::asio::buffer(message_),
//                                     boost::bind(&tcp_connection::handle_write, shared_from_this()));
//         }

//     private:
//         tcp_connection(boost::asio::io_service &io_service)
//             : socket_(io_service)
//         {
//         }

//         void handle_write()
//         {
//         }

//         tcp::socket socket_;
//         std::string message_;
// };

// class tcp_server
// {
//     public:
//         tcp_server(boost::asio::io_service &io_service)
//             : acceptor_(io_service, tcp::endpoint(tcp::v4(), 8080))
//         {
//             start_accept();
//         }

//     private:
//         void start_accept()
//         {
//             tcp_connection::pointer new_connection =
//                 tcp_connection::create(acceptor_.get_io_service());

//             acceptor_.async_accept(new_connection->socket(),
//                                 boost::bind(&tcp_server::handle_accept, this, new_connection,
//                                             boost::asio::placeholders::error));
//         }

//         void handle_accept(tcp_connection::pointer new_connection,
//                         const boost::system::error_code &error)
//         {
//             if (!error)
//             {
//                 new_connection->start();
//                 // std::make_shared<session>(std::move(new_connection->socket()))->start();
//                 start_accept();
//                 auto tmp = new_connection->socket().local_endpoint().address();
//                 std::cout << tmp << std::endl;
//             }
//         }

//         tcp::acceptor acceptor_;
// };

// class udp_server
// {
//     public:
//         udp_server(boost::asio::io_service &io_service)
//             : socket_(io_service, udp::endpoint(udp::v4(), 4086))
//         {
//             start_receive();
//         }

//     private:
//         void start_receive()
//         {
//             socket_.async_receive_from(
//                 boost::asio::buffer(recv_buffer_), remote_endpoint_,
//                 boost::bind(&udp_server::handle_receive, this,
//                             boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
//         }

//         void handle_receive(const boost::system::error_code &error, size_t bytes_transfered)
//         {
//             if (!error || error == boost::asio::error::message_size)
//             {
//                 boost::shared_ptr<std::string> message(
//                     new std::string(make_daytime_string()));

//                 socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,
//                                     boost::bind(&udp_server::handle_send, this, message));
//                 std::cout << "Receive: " << std::string(recv_buffer_.begin(), recv_buffer_.begin() + bytes_transfered) << std::endl;
//                 start_receive();
//             }
//         }

//         void handle_send(boost::shared_ptr<std::string> /*message*/)
//         {
//         }

//         udp::socket socket_;
//         udp::endpoint remote_endpoint_;
//         boost::array<char, 1> recv_buffer_;
// };