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
#include <functional>
#include <map>
#include <memory>
#include <pthread.h>
#include <sys/socket.h>
// #include <thread>

#include "Database.hpp"
#include "Packet.hpp"
#include "ServerActions.hpp"
#include "Socket.hpp"
#include "TCPSocket.hpp"
#include "UDPSocket.hpp"

#define DEFAULT_PORT 0

/*! \class Server
* \brief Class representing the Server
*
*  This class handle of the logic of the program, it loads the libraires and the protocols
*  it can switch at any given moments
*/

namespace ns
{
    using sockaddr_in = struct sockaddr_in;
    using socket_t = int;
    using client_p = std::unique_ptr<ServerClient>;

    class Server : public ServerActions
    {
        public:
            Server(const int port);
            ~Server();

            void removeClient(ServerClient);

            void PollEvent();
            void Run();
            void shutdown();

            void HandleConnection();
            void HandleReceive(ServerClient);
            
            bool updateDatabase(client_p);
            void MatchCommand(client_p client, const std::string &command);

            void Call(client_p client);

        private:
            void addSocketsToSet(socket_t *);
            bool isRunning() const;
            void initActions();

            void call(client_p);
            void hangUp(client_p);
            void infos(client_p);

            std::string buildConnectionPacket(const sockaddr_in &);
            std::string buildDisconnectionPacket(const sockaddr_in &);

            bool _status;
            unsigned short _max_connections;
            TCPSocket _sock;
            std::deque<client_p> _client_list;

            std::map<const std::string, std::function<void(
                client_p,
                std::unique_ptr<utils::pt>
            )>> _fMap;

            ServerActions sa;
            fd_set _sock_set;
            db::Database _db;
            utils::Packet _packet;
    };
}; // namespace ns