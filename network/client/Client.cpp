/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client.cpp
*/

#include "Client.hpp"

cli::Client::Client():
    _isConnected(false)
{
    if (!Sockets::Start())
    {
        std::cout << "Error initialization : " << Sockets::GetError() << std::endl;
    }
    initActions();
}

cli::Client::~Client()
{
    Sockets::Release();
}

bool cli::Client::auth()
{
    std::string ip = "127.0.0.1";
    std::string port = "8080";
    std::string username = "TOTO";
    _props.username = username;

    // std::cout << "Please enter server IP: ";
    // std::getline(std::cin, ip);
    // std::cout << "Please enter a port: ";
    // std::getline(std::cin, port);
    // std::cout << "Please enter your username: ";
    // std::getline(std::cin, username);
    return connection(ip, port, username);
}

bool cli::Client::connection(const std::string &ip, const std::string &port, const std::string &name)
{
    std::cout << "IP = " << ip << std::endl;
    std::cout << "Port = " << port << std::endl;
    std::cout << "Name = " << name << std::endl;

    if (!connectToServer(ip, std::strtoul(port.c_str(), NULL, 0))) {
        std::cerr << "Error connection: Failed to connect to server" << std::endl;
        return false;
    }
    std::cout << "Waiting to connect..." << std::endl;
    return true;
}

bool cli::Client::connectToServer(const std::string &ip, unsigned short port)
{
    if (!_socket.Connect(ip, port))
    {
        std::cerr << "Error connection: " << Sockets::GetError() << std::endl;
        return false;
    }
    setIsConnected(true);
    initListener(&_socket);
    return true;
}

void cli::Client::run()
{
    std::string input;

    while (getIsConnected()) {
        std::getline(std::cin, input);
        _packet.setType(input);
        sendMessage(_props.socket.sock, _packet.getPacket());
        _packet.clear();
        input.clear();
    }
}

void cli::Client::initStreaming()
{
    std::thread open_t(openStream);
    std::thread send_t(sendStream);

    open_t.detach();
    send_t.detach();
}

void cli::Client::openStream()
{
    while (1) {
        // recvfrom();
    }
}

void cli::Client::sendStream()
{

}

void cli::Client::sendInfos(TCPSocket *socket, props_p props)
{
    std::cout << "Sending infos..." << std::endl;
    utils::Packet packet;

    packet.setType("infos");
    packet.addData("username", props->username);
    socket->Send(packet.getPacket());
}

void cli::Client::newConnection(TCPSocket *socket, props_p props)
{
    std::cout << "New connection..." << std::endl;
}

void cli::Client::initActions()
{
    _fMap.emplace(std::make_pair("welcome", std::bind(
        Client::sendInfos, std::placeholders::_1, std::placeholders::_2
    )));
    _fMap.emplace(std::make_pair("connection", std::bind(
        Client::newConnection, std::placeholders::_1, std::placeholders::_2
    )));
}

void cli::Client::initListener(TCPSocket *socket)
{
    std::thread t1(listener,
        socket,
        _udp,
        std::make_unique<props_s>(_props),
        _fMap
    );
    t1.detach();
}

void cli::Client::setIsConnected(const bool &isConnected)
{
    _isConnected = isConnected;
}

bool cli::Client::getIsConnected() const noexcept
{
    return _isConnected;
}

void cli::Client::sendMessage(const int fd, const std::string &msg)
{
    send(fd, msg.c_str(), msg.size(), 0);
}

void cli::Client::listener(TCPSocket *socket, UDPSocket client, props_p infos,
    action_map fMap)
{
    std::stringstream ss;
    char buffer[1024];
    utils::pt root;

    std::string output;

    while (1)
    {
        std::cout << "Reading..." << std::endl;
        bzero(buffer, sizeof(buffer));
        int ret = read(socket->sock, buffer, sizeof(buffer));
        std::cout << "Received packet:" << ret << " ->\n" << buffer << std::endl;
        ss << buffer;
        try {
            boost::property_tree::read_json(ss, root);
            handleReceive(socket, root, std::move(infos), std::move(std::make_unique<action_map>(fMap)));
        } catch (std::exception &e) {
            std::cerr << "Error listener: " << e.what() << std::endl;
        }
    }
}

void cli::Client::handleReceive(TCPSocket *socket, const utils::pt packet, props_p infos,
    std::unique_ptr<action_map> fMap)
{
    try {
        std::string type = packet.get<std::string>("type");
        auto it = fMap->find(type);
        if (it != fMap->end())
            it->second(socket, std::move(infos));
        else {
            std::cerr << "No matching command found." << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw(e.what());
    }
}