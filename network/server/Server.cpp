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
    std::cout << "Listening on port " << port << std::endl;
}

Server::~Server()
{
    std::cout << "Destroying..." << std::endl;
    Sockets::CloseSocket(_sock.sock);
}

void Server::Run()
{
    while (_status) {
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
        _client_list.push_back(std::make_unique<Client>(Client(newClient)));
    }
}

void Server::HandleReceive(Client client)
{
    // std::cout << "HandleReceive" << std::endl;
    // memset(buffer, 0, 256);
    // read(client._TCP_sock.sock, buffer, sizeof(buffer)); //_sock.read(buffer);
    // std::cout << buffer << std::endl;
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
    }
    else if (valread > 0)
    {
        MatchCommand(std::move(std::make_unique<Client>(client)), buffer.erase(buffer.size()));
        // buffer[valread] = '\0';
    }
}

void Server::MatchCommand(std::unique_ptr<Client> client, const std::string &command)
{
        std::cout << "client n°" << client->_sock._sock - 3 << " sent: " << command << std::endl;
        // client->_sock.send(command);
        std::cout << "Command sent" << std::endl;
        if (command.compare("call") == 0)
        {
            for (auto &it : _client_list) {
                it->_sock.send(command);
            }
            // if (_client_list.size() > 1) {

            //     std::cout << "Calling..." << std::endl;
            //     Call(std::move(client));
            // }
            // else
            //     std::cout << "No one is connected" << std::endl;
        } else
            client->_sock.send(command);
        if (command.compare("shutdown") == 0)
            _status = false;
}

void Server::Call(std::unique_ptr<Client> client)
{
    // std::cout << "Client n°" << client->_sock._sock - 3 << std::endl;
    std::string buffer;
    std::string buffer2;
    sockaddr_in addr;
    int addrlen = sizeof(addr);
    getpeername(client->_sock._sock, (sockaddr *)&addr,
                (socklen_t *)&addrlen);
    printf("Client1, ip %s, fd %d, port %d \n",
           inet_ntoa(addr.sin_addr), client->_sock._sock,
           ntohs(addr.sin_port));
    auto it = std::find_if(_client_list.begin(), _client_list.end(),
                           [&](std::unique_ptr<Client> &i) {
                               return i->_sock._sock != client->_sock._sock;
                           })->get();
    getpeername(it->_sock._sock, (sockaddr *)&addr,
                (socklen_t *)&addrlen);
    printf("Client2, ip %s, fd %d, port %d \n",
           inet_ntoa(addr.sin_addr), it->_sock._sock,
           ntohs(addr.sin_port));
    client->_sock.read(buffer);
    it->_sock.read(buffer2);
    std::cout << "UDP Socket: " << buffer << std::endl;
    std::cout << "UDP Socket 2: " << buffer2 << std::endl;
    // client->_sock.send();
}

// Server::Server(const int port = DEFAULT_PORT):
//     _status(true)
// {
//     if (!_listen_sock.create())
//         exit(84);
//     if (!_listen_sock.bind(port, INADDR_ANY, AF_INET))
//         exit(84);
//     if (!_listen_sock.listen())
//         exit(84);
//     std::cout << "Listener on port " << port << std::endl;
// }

// Server::~Server()
// {
//     for (auto &it : _client_list) {
//         removeClient(it->_sock);
//     }
// }

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

// void Server::poll()
// {
//     socket_t max_sd = _listen_sock._sock;
//     socket_t rd = 0;

//     // add_sockets_to_set(&max_sd);
//     // rd = select(max_sd + 1, &_sock_set, NULL, NULL, NULL);
//     // if ((rd < 0) && (errno != EINTR)) {
//     //     perror("select() failed");
//     //     exit(84);
//     // }
//     // if (FD_ISSET(_listen_sock._sock, &_sock_set))
//         handleConnection();
//     // for (auto &it : _client_list)
//     //     if (FD_ISSET(it->_sock._sock, &_sock_set))
//     //         handleReceive(*it);
// }

// void Server::run()
// {
//     std::cout << "Waiting for connections..." << std::endl;
//     while (_status) {
//         poll();
//         std::cout << "..." << std::endl;
//     }
// }

// void Server::handleConnection()
// {
//     Socket new_s;
//     std::string msg = "Hello World!";
//     int addr_len = sizeof(_listen_sock._addr);

//     new_s._sock = accept(_listen_sock._sock, (sockaddr *)&_listen_sock._addr, (socklen_t *)&addr_len);
//     if (_listen_sock._sock != -1) {
//         int sock = new_s._sock;
//         sockaddr_in from = _listen_sock._addr;
//         std::thread([new_s, sock, from, this]() {
//             printf("New connection, socket fd is %d, ip is : %s, port : %d\n", sock,
//                    inet_ntoa(from.sin_addr), ntohs(from.sin_port));
//             for (;;)
//             {
//                 // char buffer[200] = {0};
//                 // int ret = recv(sock, buffer, 199, 0);
//                 std::string buffer;
//                 int ret = new_s.read(buffer);
//                 if (ret == 0 || ret == -1)
//                     break;
//                 if (buffer.compare("call\n") == 0)
//                     std::cout << "Calling..." << std::endl;
//                 if (buffer.compare("shutdown\n") == 0) {
//                     std::cout << "Shutting down server" << std::endl;
//                     shutdown();
//                     pthread_exit(NULL);
//                     exit(0);
//                 }
//                 std::cout << "[" << inet_ntoa(from.sin_addr) << " : " << ntohs(from.sin_port) << "] " << buffer << std::endl;
//                 ret = new_s.send(buffer);
//                 if (ret == 0 || ret == -1)
//                     break;
//             }
//             printf("Host disconnected, ip %s, fd %d, port %d \n",
//                    inet_ntoa(from.sin_addr), new_s._sock,
//                    ntohs(from.sin_port));
//             removeClient(new_s);
//         }).detach();
//     }
//     // if (!_listen_sock.accept(new_s)) {
//     //     perror("accept() failed");
//     //     exit(84);
//     // }
//     // printf("New connection, socket fd is %d, ip is : %s, port : %d\n", new_s._sock,
//     //        inet_ntoa(_listen_sock._addr.sin_addr), ntohs(_listen_sock._addr.sin_port));
//     // if (!new_s.send(msg))
//     //     perror("send() failed");
//     // else
//     //     std::cout << "Welcome message sent" << std::endl;
//     // _client_list.push_back(std::make_unique<Client>(Client(new_s)));
//     // printf("Adding to list of sockets as %d\n", new_s._sock);
// }

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

// void Server::handleReceive(Client client)
// {
//     int valread = 0;
//     std::string buffer;
//     int addrlen = sizeof(_listen_sock._addr);

//     if ((valread = client._sock.read(buffer)) == 0) {
//         getpeername(client._sock._sock, (struct sockaddr*)&_listen_sock._addr,
//         (socklen_t*)&addrlen);
//         printf("Host disconnected, ip %s, fd %d, port %d \n",
//             inet_ntoa(_listen_sock._addr.sin_addr), client._sock._sock,
//             ntohs(_listen_sock._addr.sin_port));
//         removeClient(client);
//     }
//     else if (valread > 0) {
//         // buffer[valread] = '\0';
//         std::cout << "client n°" << client._sock._sock - 3 << " sent: " << buffer << std::endl;
//         if (!buffer.compare("call")) {
//             std::cout << "Calling..." << std::endl;
//         }
//         if (_client_list.size() > 1) {
//             auto it = std::find_if(_client_list.begin(), _client_list.end(),
//                 [&](std::unique_ptr<Client> &i) {
//                     return i->_sock._sock != client._sock._sock;
//                 });
//             it->get()->_sock.send(buffer);
//         }
//     }
// }

// void Server::shutdown()
// {
//     _status = false;
// }
