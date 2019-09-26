/*
** EPITECH PROJECT, 2019
** CPP_babel_2019
** File description:
** client main
*/

#define MAX 80

#include "TCPSocket.hpp"
#include "UDPSocket.hpp"

#include <iostream>
#include <string.h>
#include <pthread.h>

#include <QtNetwork/QTcpSocket>

int main()
{
    // QByteArray data;

    // data.append("lol");

    QTcpSocket t;
    t.connectToHost("127.0.0.1", 4086);
    // if (t.waitForConnected()) {
    t.write("Hello World!");
    // }
    while(1);
}

// pthread_mutex_t mutexsum = PTHREAD_MUTEX_INITIALIZER;

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

// void *sendmessage(void *sock)
// {

//     char str[80];
//     char msg[100];
//     // int bufsize = maxx - 4;
//     // char *buffer = malloc(bufsize);
//     char buffer[100];
//     int sockfd = static_cast<int>(reinterpret_cast<std::uintptr_t>(sock));

//     while (1)
//     {
//         bzero(str, 80);
//         bzero(msg, 100);
//         bzero(buffer, sizeof(buffer));

//         // Get user's message
//         // mvwgetstr(bottom, input, 2, str);
//         std::cin >> str;

//         // Check for quiting
//         if (strcmp(str, "exit") == 0)
//         {

//             // done = 1;

//             // Clean up
//             pthread_mutex_destroy(&mutexsum);
//             pthread_exit(NULL);
//             close(sockfd);
//         }

//         // Send message to server
//         write(sockfd, msg, strlen(msg));

//         // scroll the top if the line number exceed height
//         pthread_mutex_lock(&mutexsum);
//         pthread_mutex_unlock(&mutexsum);
//     }
// }

// // Listen for messages and display them
// void *listener(void *sock)
// {
//     char str[80];
//     // char *buffer = malloc(bufsize);
//     char *buffer;
//     int sockfd = static_cast<int>(reinterpret_cast<std::uintptr_t>(sock));

//     while (1)
//     {
//         bzero(buffer, sizeof(buffer));
//         read(sockfd, buffer, sizeof(buffer));

//         std::cout << "=> " << buffer << std::endl;

//         // scroll the top if the line number exceed height
//         pthread_mutex_lock(&mutexsum);

//         pthread_mutex_unlock(&mutexsum);
//     }
// }

// int main()
// {
//     if (!Sockets::Start())
//     {
//         std::cout << "Error initialization : " << Sockets::GetError() << std::endl;
//         return 0;
//     }

//     TCPSocket socket;
//     if (!socket.Connect("127.0.0.1", 4086))
//     {
//         std::cout << "Error connection : " << Sockets::GetError() << std::endl;
//         return 0;
//     }
//     std::cout << "Socket connected !" << std::endl;
//     // UDPSocket udp_socket;
//     // func(socket.getSocket());
//     pthread_t threads[2];
//     pthread_attr_t attr;
//     pthread_attr_init(&attr);
//     pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

//     int sockfd = socket.getSocket();

//     pthread_create(&threads[0], &attr, sendmessage, (void *)sockfd);
//     pthread_create(&threads[1], &attr, listener, (void *)sockfd);
//     while (1);
//     Sockets::Release();
// }
