/*
** EPITECH PROJECT, 2019
** Server_CPP
** File description:
** Server
*/

#include "Server.hpp"

Server::Server(const int port = DEFAULT_PORT):
    _status(true)
{
    if (!_listen_sock.create())
        exit(84);
    if (!_listen_sock.bind(port, INADDR_ANY, AF_INET))
        exit(84);
    if (!_listen_sock.listen())
        exit(84);
    std::cout << "Listener on port " << port << std::endl;
}

void Server::add_sockets_to_set(socket_t *max_sd)
{
    socket_t sd = 0;

    FD_ZERO(&_sock_set);
    FD_SET(_listen_sock._sock, &_sock_set);
    *max_sd = _listen_sock._sock;
    for (auto &it : _client_list) {
        sd = it->_sock._sock;
        if (sd > 0)
            FD_SET(sd, &_sock_set);
        if (sd > *max_sd)
            *max_sd = sd;
    }
}

void Server::poll()
{
    socket_t max_sd = _listen_sock._sock;
    socket_t rd = 0;

    add_sockets_to_set(&max_sd);
    rd = select(max_sd + 1, &_sock_set, NULL, NULL, NULL);
    if ((rd < 0) && (errno != EINTR)) {
        perror("select() failed");
        exit(84);
    }
    if (FD_ISSET(_listen_sock._sock, &_sock_set))
        handleConnection();
    for (auto &it : _client_list)
        if (FD_ISSET(it->_sock._sock, &_sock_set))
            handleReceive(*it);
}

void Server::run()
{
    std::cout << "Waiting for connections..." << std::endl;
    while (_status)
        poll();
}

void Server::handleConnection()
{
    Socket new_s;
    std::string msg = "Hello World!";

    if (!_listen_sock.accept(new_s)) {
        perror("accept() failed");
        exit(84);
    }
    printf("New connection, socket fd is %d, ip is : %s, port : %d\n", new_s._sock,
           inet_ntoa(_listen_sock._addr.sin_addr), ntohs(_listen_sock._addr.sin_port));
    if (!new_s.send(msg))
        perror("send() failed");
    _client_list.push_back(std::make_unique<Client>(Client(new_s)));
    printf("Adding to list of sockets as %d\n", new_s._sock);
}

void Server::removeClient(Client client)
{
    close(client._sock._sock);
    auto it = std::find_if(_client_list.begin(), _client_list.end(),
        [&](std::unique_ptr<Client> &i) {
            return i->_sock._sock == client._sock._sock;
        });
    if (it != _client_list.end())
        _client_list.erase(it);
}

void Server::handleReceive(Client client)
{
    int valread = 0;
    std::string buffer;
    int addrlen = sizeof(_listen_sock._addr);

    if ((valread = client._sock.read(buffer)) == 0) {
        getpeername(client._sock._sock, (struct sockaddr*)&_listen_sock._addr,
        (socklen_t*)&addrlen);
        printf("Host disconnected, ip %s, fd %d, port %d \n",
            inet_ntoa(_listen_sock._addr.sin_addr), client._sock._sock,
            ntohs(_listen_sock._addr.sin_port));
        removeClient(client);
    }
    else if (valread > 0) {
        // buffer[valread] = '\0';
        std::cout << "client n°" << client._sock._sock - 3 << " sent: " << buffer << std::endl;
        if (_client_list.size() > 1) {
            auto it = std::find_if(_client_list.begin(), _client_list.end(),
                [&](std::unique_ptr<Client> &i) {
                    return i->_sock._sock != client._sock._sock;
                });
            it->get()->_sock.send(buffer);
        }
    }
}

void Server::shutdown()
{
    _status = false;
}