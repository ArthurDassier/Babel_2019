/*
** EPITECH PROJECT, 2019
** Server_CPP
** File description:
** Server
*/

#include "Server.hpp"

Server::Server(const int port = DEFAULT_PORT):
    _status(true),
    _max_connections(5)
{
    if (!_sock.ListenOn(port, _max_connections)) {
        std::cerr << "ERRRROR" << std::endl;
        throw "Socket not available";
    }
    initActions();
    std::cout << "Listening on port " << port << " and fd n°" << _sock.sock << std::endl;
}

Server::~Server()
{
    std::cout << "Destroying..." << std::endl;
    Sockets::CloseSocket(_sock.sock);
}

void Server::Run()
{
    while (isRunning()) {
        PollEvent();
    }
}

void Server::PollEvent()
{
    socket_t max_sd = _sock.sock;
    socket_t rd = 0;

    add_sockets_to_set(&max_sd);
    rd = select(max_sd + 1, &_sock_set, NULL, NULL, NULL);
    if ((rd < 0) && (errno != EINTR)) {
        perror("select() failed");
        exit(84);
    }
    if (FD_ISSET(_sock.sock, &_sock_set))
        HandleConnection();
    for (auto &it : _client_list)
        if (FD_ISSET(it->_sock._sock, &_sock_set))
            HandleReceive(*it);
}

void Server::HandleConnection()
{
    // TCPSocket newClient;
    Socket newClient;
    sockaddr_in from = {0};
    socklen_t addrlen = sizeof(from);

    newClient._sock = accept(_sock.sock, (sockaddr *)&from, &addrlen);
    if (newClient._sock != INVALID_SOCKET)
    {
        printf("New connection, socket fd is %d, ip is : %s, port : %d\n", newClient._sock,
           inet_ntoa(from.sin_addr), ntohs(from.sin_port));
        newClient.send("Hello World!\n");
        _packet.setType("connection");
        _packet.addData("ip", inet_ntoa(from.sin_addr));
        _packet.addData("port", ntohs(from.sin_port));
        for (auto &it : _client_list)
            it->_sock.send(_packet.getPacket());
        _packet.clear();
        _client_list.push_back(std::make_unique<ServerClient>(ServerClient(newClient)));
    }
}

void Server::HandleReceive(ServerClient client)
{
    int valread = 0;
    std::string buffer;
    sockaddr_in addr;
    int addrlen = sizeof(addr);

    if ((valread = client._sock.read(buffer)) == 0)
    {
        getpeername(client._sock._sock, (sockaddr *)&addr,
                    (socklen_t *)&addrlen);
        printf("Host disconnected, ip %s, fd %d, port %d \n",
           inet_ntoa(addr.sin_addr), client._sock._sock,
           ntohs(addr.sin_port));
        removeClient(client);
    } else if (valread > 0) {
        MatchCommand(std::move(std::make_unique<ServerClient>(client)), buffer.erase(buffer.size()));
    }
}

void Server::MatchCommand(std::unique_ptr<ServerClient> client, const std::string &command)
{
        std::cout << "client n°" << client->_sock._sock - 3 << " sent:\n" << command << std::endl;

        if (command.compare("call") != 0)
            for (auto &it : _client_list)
            {
                it->_sock.send(_packet.getPacket());
            }
        else {
            auto it = _fMap.find(command);
            if (it != _fMap.end()) {
                std::vector<std::unique_ptr<ServerClient>> client_list;
                auto other = std::find_if(_client_list.begin(), _client_list.end(),
                    [&](std::unique_ptr<ServerClient> &i) {
                        return i->_sock._sock != client->_sock._sock;
                    });
                it->second(std::move(client));
                // it->second(std::move(client), std::make_unique<ServerClient>(other)); //client_list);
            }
        }
        // _packet.setType("test");
        // _packet.addData("ip", "127.0.0.1");
}

void Server::add_sockets_to_set(socket_t *max_sd)
{
    socket_t sd = 0;

    FD_ZERO(&_sock_set);
    FD_SET(_sock.sock, &_sock_set);
    *max_sd = _sock.sock;
    for (auto &it : _client_list) {
        sd = it->_sock._sock;
        if (sd > 0)
            FD_SET(sd, &_sock_set);
        if (sd > *max_sd)
            *max_sd = sd;
    }
}

void Server::removeClient(ServerClient client)
{
    close(client._sock._sock);
    auto it = std::find_if(_client_list.begin(), _client_list.end(),
        [&](std::unique_ptr<ServerClient> &i) {
            return i->_sock._sock == client._sock._sock;
        });
    if (it != _client_list.end())
        _client_list.erase(it);
}

bool Server::isRunning() const
{
    return _status;
}

void Server::initActions()
{
    _fMap.emplace(std::make_pair("call", std::bind(&ServerActions::InitConnection, this, std::placeholders::_1)));
}