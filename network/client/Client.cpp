/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** Client.cpp
*/

#include "Client.hpp"

Client::Client() //const std::string ip, unsigned short port)
{
    if (!Sockets::Start())
    {
        std::cout << "Error initialization : " << Sockets::GetError() << std::endl;
    }
    // initListener(_socket.sock);
    // std::thread t_udp(UDPListener, _udp);
    // t_udp.detach();
}

Client::~Client()
{
    Sockets::Release();
}

void Client::connectToServer(const std::string ip, unsigned short port)
{
    if (!_socket.Connect(ip, port))
    {
        std::cerr << "Error connection: " << Sockets::GetError() << std::endl;
    }
    initListener(_socket.sock);
}

void Client::initStreaming()
{
    std::thread open_t(openStream);
    std::thread send_t(sendStream);

    open_t.detach();
    send_t.detach();
}

void Client::openStream()
{
    while (1) {
        // recvfrom();
    }
}

void Client::sendStream()
{

}

void Client::initListener(int sock)
{

}

// void Client::sendMessage(const int fd, const std::string msg)
// {
//     send(fd, msg.c_str(), msg.size(), 0);
// }

// void Client::askForCall(UDPSocket client)
// {
//     const char *msg = "Try";
//     sendto(client.sock, msg, strlen(msg),
//            MSG_CONFIRM, (const sockaddr *)&client.addr, sizeof(client.addr));
//     std::cout << "Sent to" << client.sock << std::endl;
// }

// void Client::Run()
// {
//     std::string str;
//     char buffer[1024];
//     ssize_t n = 0;
//     socklen_t len = 0;
//     sockaddr_in serverAddr;

//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_port = htons(5000);
//     serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
//     _udp.Bind(0);
//     socklen_t addrlen = sizeof(_udp.getAddr());
//     // std::cout << "udp fd: " << _udp.sock << std::endl;
//     // std::cout << "udp port: " << ntohs(_udp.addr.sin_port) << std::endl;
//     // std::cout << "udp addr" << inet_ntoa(_udp.addr.sin_addr) << std::endl;
//     _packet.setType("contact");
//     _packet.addData("sock", _udp.sock);
//     _packet.addData("port", _udp.addr.sin_port);
//     _packet.addData("addr", inet_ntoa(_udp.addr.sin_addr));
//     while (1)
//     {
//         std::cout << "Your message: ";
//         std::cin >> str;
//         if (str.compare("call") == 0) {
//             sendMessage(_socket.sock, _packet.getPacket());
//             _packet.clear();
//         }
//         else
//             sendMessage(_socket.sock, str);
//     }
// }

// void Client::initListener(int sockfd)
// {
//     // pthread_t thread;
//     // pthread_attr_t attr;
//     // pthread_attr_init(&attr);
//     // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
//     // pthread_create(&thread, &attr, Listener, reinterpret_cast<void *>(sockfd));
//     std::thread t1(Listener, sockfd, _udp);
//     t1.detach();
// }

// void Client::Listener(int sock, UDPSocket client)
// {
//     // int sockfd = static_cast<int>(reinterpret_cast<std::uintptr_t>(sock));
//     char buffer[1024];

//     while (1)
//     {
//         std::cout << "Reading..." << std::endl;
//         bzero(buffer, sizeof(buffer));
//         int ret = read(sock, buffer, sizeof(buffer));
//         std::cout << "ret: " << ret << "-> " << buffer << std::endl;
//         if (strcmp(buffer, "call") == 0) {
//             askForCall(client);
//         }
//     }
// }

// // void Client::UDPListener(UDPSocket client)
// // {
// //     char buffer[1024];
// //     ssize_t n = 0;
// //     socklen_t len = sizeof(client.addr);

// //     while (1) {
// //         // puts("while looping");
// //         n = recvfrom(client.sock, buffer, 1024, 0, (struct sockaddr *)&client.addr, &len);
// //         sendto(client.sock, buffer, sizeof(buffer), 0,
// //             (struct sockaddr *)&client.addr, len);
// //     }
// // }
