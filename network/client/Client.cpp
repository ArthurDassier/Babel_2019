/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client.cpp
*/

#include "Client.hpp"

#define MAXLINE 1024

// int PORT = 0;

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
    std::string port = "4086";
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

void cli::Client::run(char *argv[])
{
    std::string input;

    while (getIsConnected()) {
        std::getline(std::cin, input);
        _packet.setType(input);
        sendMessage(_socket.sock, _packet.getPacket());
        if (input.compare("call") == 0)
            initStreaming(std::atoi(argv[2]));
        _packet.clear();
        input.clear();
    }
}

static void readStream(int udpSocket, sockaddr_in serverStorage)
{
    int nBytes;
    char buffer[1024];
    socklen_t addr_size, client_addr_size;
    int i;
    addr_size = sizeof serverStorage;
    while (1)
    {
        bzero(buffer, sizeof(buffer));
        // std::cout << "RECV LOOP" << std::endl;
        nBytes = recvfrom(udpSocket, buffer, 1024, 0, (struct sockaddr *)&serverStorage, &addr_size);
        // std::cout << buffer << std::endl;
    }
}

void cli::Client::initStreaming(int PORT)
{
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;

    // Creating socket file descriptor
    // PORT = std::atoi(argv[2]);
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    std::cout << "Sockfd: " << sockfd << std::endl;

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    std::cout << "serveraddr: " << (PORT != 8080 ? 4086 : 8080) << std::endl;
    servaddr.sin_port = htons(PORT != 8080 ? 4086 : 8080);
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    clientaddr.sin_family = AF_INET;
    std::cout << "clientaddr: " << PORT << std::endl;
    clientaddr.sin_port = htons(PORT == 8080 ? 4086 : 8080);
    clientaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr));

    std::string msg = "lol";

    int n = 0;
    socklen_t len = 0;
    PortAudio test;
    std::vector<unsigned short> tmp;

    std::thread open_t(readStream, sockfd, clientaddr);
    open_t.detach();
    // while (1)
    // {
        std::cout << "SEND LOOP" << std::endl;
        // std::cin >> msg;
        PaStream *stream;
        test.SetInputParameters();
        std::cout << "1" << std::endl;
        test.SetData(5, 44100, 2);
        std::cout << "2" << std::endl;
        stream = test.RecordStream();
        std::cout << "3" << std::endl;
        test.StartStream(stream);
        Pa_Sleep(3000);
        // sleep(3000);
        tmp = test.readStream(stream);
        std::vector<unsigned char> encoded =
            _encoder.encode(tmp);
        std::string encoded_msg(encoded.begin(), encoded.end());
        std::cout << encoded_msg << std::endl;
        test.CloseStream(stream);
        _packet.setType("audio");
        // _packet.addData("data", encoded_msg);
        sendto(sockfd, _packet.getPacket().c_str(), _packet.getPacket().size(),
               MSG_CONFIRM, (const struct sockaddr *)&servaddr,
               sizeof(servaddr));
        _packet.clear();
        // test.SetOutputParameters();
        // test.setDataFrameIndex();
        // test.PlayStream(stream);
        // test.StartStream(stream);
        // Pa_Sleep(3000);
        // test.CloseStream(stream);
        msg.clear();
    // }
    close(sockfd);
}

void cli::Client::openStream()
{
    PortAudio test;
    PaStream *stream;
    // std::vector<unsigned short> stream;

    // do {
        test.SetInputParameters();
        std::cout << "1" << std::endl;
        test.SetData(5, 44100, 2);
        std::cout << "2" << std::endl;
        stream = test.RecordStream();
        std::cout << "3" << std::endl;
        // std::vector<unsigned char> encoded =
        //     _encoder.encode(stream);
        // std::string encoded_msg(encoded.begin(), encoded.end());
        // test.StartStream(stream);
        // std::cout << "4" << std::endl;
        // Pa_Sleep(3000);
        // std::cout << "5" << std::endl;
        // test.CloseStream(stream);
        // std::cout << "6" << std::endl;
        // test.SetOutputParameters();
        // test.setDataFrameIndex();
        // std::cout << "7" << std::endl;
        // // test.PlayStream(stream);
        // // std::cout << "8" << std::endl;
        // // test.StartStream(stream);
        Pa_Sleep(5);
        sleep(5);
        // std::cout << "9" << std::endl;
        _packet.setType("audio");
        // _packet.addData("data", encoded_msg);
        std::cout << _packet.getPacket() << std::endl;
        _socket.Send(_packet.getPacket());
        _packet.clear();
        // test.CloseStream(stream);
        // std::cout << "10" << std::endl;
    // } while (true);
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

void cli::Client::playStream(PaStream *stream)
{
    PortAudio test;

    std::cout << "1" << std::endl;
    test.SetData(5, 44100, 2);
    std::cout << "2" << std::endl;
    // stream = test.RecordStream();
    // std::cout << "3" << std::endl;
    // test.SetOutputParameters();
    // std::cout << "4" << std::endl;
    // test.setDataFrameIndex();
    // std::cout << "5" << std::endl;
    // test.PlayStream(stream);
    // std::cout << "6" << std::endl;
    // std::cout << "play stream" << std::endl;
}

void cli::Client::initActions()
{
    _fMap.emplace(std::make_pair("welcome", std::bind(
        Client::sendInfos, std::placeholders::_1, std::placeholders::_2
    )));
    _fMap.emplace(std::make_pair("connection", std::bind(
        Client::newConnection, std::placeholders::_1, std::placeholders::_2
    )));
    // _fMap.emplace(std::make_pair("call", std::bind(
    //     Client::initStreaming, std::placeholders::_1
    // )));
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
    EncoderSystem encoder;
    try
    {
        std::string type = packet.get<std::string>("type");
        if (type.compare("audio") == 0) {
            std::string data = packet.get<std::string>("data");
            std::vector<unsigned char> encoded;
            for (auto &it : data)
                encoded.push_back(it);
            PortAudio test;
            PaStream *stream;
            test.SetOutputParameters();
            test.setDataFrameIndex();
            std::vector<unsigned short> decoded = encoder.decode(encoded);
            stream = test.writeStream(decoded);
            test.PlayStream(stream);
            test.StartStream(stream);
            Pa_Sleep(3000);
            test.CloseStream(stream);
            // std::cout << stream << std::endl;
            // playStream(&stream);
            std::cout << "play stream" << std::endl;
        }
        else if (type.compare("call") == 0) {
            // initStreaming(_udp_port);
        }
        else
        {
            auto it = fMap->find(type);
            if (it != fMap->end())
                it->second(socket, std::move(infos));
            else {
                std::cerr << "No matching command found." << std::endl;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        throw(e.what());
    }
}