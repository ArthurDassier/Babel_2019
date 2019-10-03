/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** client main
*/

#define MAX 80

#include "Client.hpp"
#include "TCPSocket.hpp"
#include "UDPSocket.hpp"

#include <iostream>
#include <string.h>
#include <pthread.h>

#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#define MAX 80
#define PORT 4086
#define SA struct sockaddr

// int main(__attribute__((unused)) int argc, char **argv)
// {
//     TCPSocket sock;
//     UDPSocket udp;
//     // char buff[256];
//     std::string buff;

//     sock.Connect("127.0.0.1", std::stoi(argv[1]));
//     udp.Bind(0);
//     std::cout << "UDP binded on port " << udp.sock << std::endl;
//     while (1) {
//         // bzero(buff, sizeof(buff));
//         int ret = sock.Read(buff);
//         // int ret = read(sock.sock, buff, sizeof(buff));
//         // if (ret != )
//         std::cout << "Receive from server: " << buff << std::endl;
//         buff.clear();
//         std::string input;
//         std::cin >> input;
//         sock.Send(input);
//         std::cout << "'" << input << "' sent" << std::endl;
//         // if (input.compare("call") == 0) {
//         //     std::cout << "Try to call" << std::endl;
//         //     int ret = sock.Read(buff);
//         //     if (buff.compare("call") == 0) {
//         //         std::cout << "Handling call..." << std::endl;
//         //         sock.Send(std::to_string(udp.sock));
//         //     }
//         // }
//         input.clear();
//     }
//     // sock.Receive();
//     return (0);
// }

// void func(int sockfd)
// {
//     char buff[MAX];
//     int n;
//     int ret = 0;

//     std::cout << "Pourquoi rien ne s'est affiché? (4)" << std::endl;
//     for (;;)
//     {
//         bzero(buff, sizeof(buff));
//         printf("Enter the string : ");
//         n = 0;
//         while ((buff[n++] = getchar()) != '\n')
//             ;
//         ret = send(sockfd, buff, sizeof(buff), 0);
//         if (ret != 0)
//             std::cout << "FUCK 1\n";
//         std::cout << "Pourquoi rien ne s'est affiché? (5)" << std::endl;
//         // bzero(buff, sizeof(buff));
//         memset(buff, 0, MAX + 1);
//         ret = read(sockfd, buff, sizeof(buff));
//         if (ret != 0)
//             std::cout << "FUCK 2\n";
//         printf("From Server : %s", buff);
//         std::cout << "Pourquoi rien ne s'est affiché? (6)" << std::endl;
//         if ((strncmp(buff, "exit", 4)) == 0)
//         {
//             printf("Client Exit...\n");
//             break;
//         }
//     }
// }

// int main()
// {
//     int sockfd, connfd;
//     struct sockaddr_in servaddr, cli;

//     // socket create and varification
//     sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//     if (sockfd == -1)
//     {
//         printf("socket creation failed...\n");
//         exit(0);
//     }
//     else
//         printf("Socket successfully created..\n");

//     std::cout << "Pourquoi rien ne s'est affiché? (1)" << std::endl;
//     bzero(&servaddr, sizeof(servaddr));

//     // assign IP, PORT
//     servaddr.sin_family = AF_INET;
//     servaddr.sin_addr.s_addr = INADDR_ANY; //inet_addr("127.0.0.1");
//     servaddr.sin_port = htons(PORT);

//     std::cout << "Pourquoi rien ne s'est affiché? (2)" << std::endl;

//     // connect the client socket to server socket
//     if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
//     {
//         printf("connection with the server failed...\n");
//         exit(0);
//     }
//     else
//         printf("connected to the server..\n");

//     // function for chat

//     std::cout << "Pourquoi rien ne s'est affiché? (3)" << std::endl;
//     func(sockfd);

//     std::cout << "Pourquoi rien ne s'est affiché?" << std::endl;

//     // close the socket
//     close(sockfd);
// }

pthread_mutex_t mutexsum = PTHREAD_MUTEX_INITIALIZER;

// void func(int sockfd)
// {
//     char buff[MAX];
//     int n;
//     for (;;)
//     {
//         bzero(buff, sizeof(buff));
//         printf("Enter the string : ");
//         n = 0;
//         while ((buff[n++] = getchar()) != '\n');
//         if (send(sockfd, buff, sizeof(buff), 0) < 0)
//             exit(5);
//         if (recv(sockfd, buff, sizeof(buff), 0) < 0)
//             exit(6);
//         // write(sockfd, buff, sizeof(buff));
//         // bzero(buff, sizeof(buff));
//         // read(sockfd, buff, sizeof(buff));
//         printf("From Server : %s", buff);
//         if ((strncmp(buff, "exit", 4)) == 0)
//         {
//             printf("Client Exit...\n");
//             break;
//         }
//     }
// }

void *sendmessage(void *sock)
{

    char str[80];
    char msg[100];
    // int bufsize = maxx - 4;
    // char *buffer = malloc(bufsize);
    // char buffer[1024];
    int sockfd = static_cast<int>(reinterpret_cast<std::uintptr_t>(sock));

    while (1)
    {
        bzero(str, 80);
        bzero(msg, 100);
        // bzero(buffer, sizeof(buffer));

        // Get user's message
        // mvwgetstr(bottom, input, 2, str);
        std::cout << "Your message: ";
        std::cin >> str;

        std::cout << "'" << str << "' sent" << std::endl;

        // Check for quiting
        if (strcmp(str, "exit") == 0)
        {

            // done = 1;

            // Clean up
            pthread_mutex_destroy(&mutexsum);
            pthread_exit(NULL);
            close(sockfd);
        }

        // Send message to server
        std::cout << "write on fd n°" << sockfd << std::endl;
        send(sockfd, msg, strlen(msg), 0);

        // scroll the top if the line number exceed height
        // pthread_mutex_lock(&mutexsum);
        // pthread_mutex_unlock(&mutexsum);
    }
}

// Listen for messages and display them
void *listener(void *sock)
{
    char str[80];
    // char *buffer = malloc(bufsize);
    char buffer[1024];
    int sockfd = static_cast<int>(reinterpret_cast<std::uintptr_t>(sock));

    while (1)
    {
        std::cout << "Reading..." << std::endl;
        bzero(buffer, sizeof(buffer));
        int ret = read(sockfd, buffer, sizeof(buffer));
        std::cout << "ret: " << ret << "-> " << buffer << std::endl;
        boost::property_tree::ptree root;
        std::stringstream ss;

        ss << buffer;
        try
        {
            boost::property_tree::read_json(ss, root);
        }
        catch (std::exception &e)
        {
            std::cerr << "Client Error: " << e.what() << std::endl;
            // throw(error::ClientError(e.what()));
        }
        // if (strcmp(buffer, "end") == 0)
        // {
        //     pthread_exit(NULL);
        //     close(sockfd);
        //     break;
        // }

        std::cout << "=> " << buffer << std::endl;

        // scroll the top if the line number exceed height
        // pthread_mutex_lock(&mutexsum);

        // pthread_mutex_unlock(&mutexsum);
    }
}

int main(__attribute__((unused)) int argc, char **argv)
{
    Client client;
    //(argv[1], std::atoi(argv[2]));

    client.connectToServer(argv[1], std::atoi(argv[2]));
    client.run();
    // if (!Sockets::Start())
    // {
    //     std::cout << "Error initialization : " << Sockets::GetError() << std::endl;
    //     return 0;
    // }

    // TCPSocket socket;
    // if (!socket.Connect("127.0.0.1", std::atoi(argv[1])))
    // {
    //     std::cout << "Error connection : " << Sockets::GetError() << std::endl;
    //     return 0;
    // }
    // std::cout << "Socket connected !" << std::endl;
    // // UDPSocket udp_socket;
    // // func(socket.getSocket());
    // pthread_t threads[2];
    // pthread_attr_t attr;
    // pthread_attr_init(&attr);
    // pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // int sockfd = socket.sock;
    // std::string str;

    // // pthread_create(&threads[0], &attr, sendmessage, reinterpret_cast<void *>(sockfd));
    // pthread_create(&threads[1], &attr, listener, reinterpret_cast<void *> (sockfd));
    // while (1) {
    //     std::cout << "Your message: ";
    //     std::cin >> str;
    //     send(sockfd, str.c_str(), str.size(), 0);
    // }
    // Sockets::Release();
}
