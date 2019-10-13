/*
** EPITECH PROJECT, 2019
** Server_CPP
** File description:
** Server
*/

#include "Server.hpp"

/*!
 * \fn ns::Server::Server(const int port = DEFAULT_PORT)
 * \brief Open connection with port in param
 *
 * \param int port representing the port
 */

ns::Server::Server(const int port = DEFAULT_PORT):
    _status(true),
    _max_connections(5),
    _db("babel_server.db")
{
    if (!Sockets::Start())
        std::cout << "Error initialization : " << Sockets::GetError() << std::endl;
    if (!_sock.ListenOn(port, _max_connections)) {
        std::cerr << "ERRRROR" << std::endl;
        throw "Socket not available";
    }
    initActions();
    _db.createTable("CLIENT("
                    "ID INT PRIMARY KEY     NOT NULL,"
                    "NAME           TEXT    NOT NULL,"
                    "DATE           TEXT)");
}

/*!
 * \fn ns::Server::~Server()
 * \brief Destroy the Server by reseting the shared pointers
 *
 * \param void
 */

ns::Server::~Server()
{
    std::cout << "Destroying..." << std::endl;
    Sockets::CloseSocket(_sock.sock);
}

/*!
 * \fn ns::Server::Run()
 * \brief Run the server
 *
 * \param void
 */

void ns::Server::Run()
{
    while (isRunning()) {
        PollEvent();
    }
}

/*!
 * \fn ns::Server::PollEvent()
 * \brief Poll the event
 *
 * \param void
 */

void ns::Server::PollEvent()
{
    socket_t max_sd = _sock.sock;
    socket_t rd = 0;

    addSocketsToSet(&max_sd);
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

/*!
 * \fn ns::Server::HandleConnection()
 * \brief Handle connection
 *
 * \param void
 */

void ns::Server::HandleConnection()
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
        auto client = std::make_unique<ServerClient>(ServerClient(newClient));
        // if (updateDatabase(std::move(client)) == true)
        //     std::cout << "New client created in Database" << std::endl;
        // else {
        //     std::cerr << "PAS BON" << std::endl;
        //     exit(1);
        // }
        _packet.setType("welcome");
        newClient.send(_packet.getPacket());
        std::string connectionPacket = buildConnectionPacket(from);
        for (auto &it : _client_list)
            it->_sock.send(connectionPacket);
        _client_list.push_back(std::move(client));
    }
}

/*!
 * \fn ns::Server::HandleReceive(ServerClient client)
 * \brief Handle receive
 *
 * \param ServerClient client
 */

void ns::Server::HandleReceive(ServerClient client)
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
        for (auto &it : _client_list)
            it->_sock.send(buildDisconnectionPacket(addr));
    }
    else if (valread > 0)
        MatchCommand(std::move(std::make_unique<ServerClient>(client)), buffer);
}

/*!
 * \fn ns::Server::updateDatabase(client_p client)
 * \brief updtae database
 *
 * \param client_p client
 */

bool ns::Server::updateDatabase(client_p client)
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    std::ostringstream oss;

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d%m%Y-%H:%M:%S", timeinfo);
    oss << "DATE = '" << buffer << "' where NAME = '" << client->getUsername() << "'";
    try {
        if (!_db.upsertData("CLIENT", oss.str())) {
            auto new_client = std::make_unique<db::ClientDatabase>(
                client->getUsername(), rawtime
            );
            return _db.insertData(std::move(new_client));
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 1;
}

/*!
 * \fn ns::Server::MatchCommand(client_p client, const std::string &packet)
 * \brief Match command
 *
 * \param client_p client, const std::string &packet
 */

void ns::Server::MatchCommand(client_p client, const std::string &packet)
{
    std::stringstream ss;
    utils::pt root;

    ss << packet;
    try {
        boost::property_tree::read_json(ss, root);
        std::string command = root.get<std::string>("type");
        std::cout << "command: " << command << std::endl;
        auto it = _fMap.find(command);
        if (it != _fMap.end()) {
            it->second(std::move(client), std::move(std::make_unique<utils::pt>(root)));
        }
    } catch (const std::exception &e) {
        std::cerr << "Read json errror: " << e.what() << std::endl;
    }
}

/*!
 * \fn ns::Server::addSocketsToSet(socket_t *max_sd)
 * \brief add socket
 *
 * \param socket_t *max_sd
 */

void ns::Server::addSocketsToSet(socket_t *max_sd)
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

/*!
 * \fn ns::Server::removeClient(ServerClient client)
 * \brief remove pecno
 *
 * \param ServerClient client
 */

void ns::Server::removeClient(ServerClient client)
{
    close(client._sock._sock);
    auto it = std::find_if(_client_list.begin(), _client_list.end(),
        [&](client_p &i) {
            return i->_sock._sock == client._sock._sock;
        });
    if (it != _client_list.end())
        _client_list.erase(it);
}

/*!
 * \fn ns::Server::isRunning() const
 * \brief Handle connection
 *
 * \param void
 */

bool ns::Server::isRunning() const
{
    return _status;
}

/*!
 * \fn ns::Server::initActions()
 * \brief init actions
 *
 * \param void
 */

void ns::Server::initActions()
{
    _fMap.emplace(std::make_pair("call", std::bind(&ServerActions::initConnection, this, std::placeholders::_1)));
    _fMap.emplace(std::make_pair("hang_up", std::bind(&ServerActions::closeConnection, this, std::placeholders::_1)));
    _fMap.emplace(std::make_pair("infos", std::bind(&Server::infos, this, std::placeholders::_1)));
}

/*!
 * \fn ns::Server::call(client_p client)
 * \brief Calling guys
 *
 * \param client_p client
 */

void ns::Server::call(client_p client)
{
}

/*!
 * \fn ns::Server::hangUp(client_p client)
 * \brief Rccroche guys
 *
 * \param client_p client
 */

void ns::Server::hangUp(client_p client)
{

}

/*!
 * \fn ns::Server::infos(client_p client)
 * \brief Handle connection
 *
 * \param client_p client
 */

void ns::Server::infos(client_p client)
{
    std::cout << "OK cool mon pote" << std::endl;
    _packet.clear();
    _packet.setType("response");
    _packet.addData("code", 200);
    client->_sock.send(_packet.getPacket());
}

/*!
 * \fn ns::Server::buildConnectionPacket(const sockaddr_in &new_client)
 * \brief build the conection packet
 *
 * \param const sockaddr_in &new_client
 */

std::string ns::Server::buildConnectionPacket(const sockaddr_in &new_client)
{
    _packet.clear();
    _packet.setType("connection");
    _packet.addData("ip", inet_ntoa(new_client.sin_addr));
    _packet.addData("port", ntohs(new_client.sin_port));
    return _packet.getPacket();
}

/*!
 * \fn ns::Server::buildDisconnectionPacket(const sockaddr_in &client)
 * \brief build disconnect packet
 *
 * \param const sockaddr_in &client
 */

std::string ns::Server::buildDisconnectionPacket(const sockaddr_in &client)
{
    _packet.clear();
    _packet.setType("disconnection");
    _packet.addData("ip", inet_ntoa(client.sin_addr));
    _packet.addData("port", ntohs(client.sin_port));
    return _packet.getPacket();
}