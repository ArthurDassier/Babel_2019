// // // Server side implementation of UDP client-server model
// // #include <stdio.h>
// // #include <stdlib.h>
// // #include <unistd.h>
// // #include <string.h>
// // #include <sys/types.h>
// // #include <sys/socket.h>
// // #include <arpa/inet.h>
// // #include <netinet/in.h>

// // #define PORT 8080
// // #define MAXLINE 1024

// // // Driver code
// // int main()
// // {
// //     int sockfd;
// //     char buffer[MAXLINE];
// //     char *hello = "Hello from server";
// //     struct sockaddr_in servaddr, cliaddr;

// //     // Creating socket file descriptor
// //     if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
// //     {
// //         perror("socket creation failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     memset(&servaddr, 0, sizeof(servaddr));
// //     memset(&cliaddr, 0, sizeof(cliaddr));

// //     // Filling server information
// //     servaddr.sin_family = AF_INET; // IPv4
// //     servaddr.sin_addr.s_addr = INADDR_ANY;
// //     servaddr.sin_port = htons(PORT);

// //     // Bind the socket with the server address
// //     if (bind(sockfd, (const struct sockaddr *)&servaddr,
// //              sizeof(servaddr)) < 0)
// //     {
// //         perror("bind failed");
// //         exit(EXIT_FAILURE);
// //     }

// //     while (1) {
// //         int len, n;
// //         n = recvfrom(sockfd, (char *)buffer, MAXLINE,
// //                         MSG_WAITALL, (struct sockaddr *)&cliaddr,
// //                         &len);
// //         buffer[n] = '\0';
// //         printf("Client : %d -> %s\n", cliaddr.sin_addr.s_addr, buffer);
// //         sendto(sockfd, (const char *)hello, strlen(hello),
// //                 MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
// //                 len);
// //         printf("Hello message sent.\n");
// //     }
// //     return 0;
// // }

// static char ibmcopyr[] =
//     "UDPS     - Licensed Materials - Property of IBM. "
//     "This module is \"Restricted Materials of IBM\" "
//     "5647-A01 (C) Copyright IBM Corp. 1992, 1996. "
//     "See IBM Copyright Instructions.";

// #include <arpa/inet.h>
// #include <netdb.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

// main()
// {
//     int s, namelen, client_address_size;
//     struct sockaddr_in client, server;
//     char buf[32];

//     /*
//     * Create a datagram socket in the internet domain and use the
//     * default protocol (UDP).
//     */
//     if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
//     {
//         perror("socket()");
//         exit(1);
//     }

//     /*
//     * Bind my name to this socket so that clients on the network can
//     * send me messages. (This allows the operating system to demultiplex
//     * messages and get them to the correct server)
//     *
//     * Set up the server name. The internet address is specified as the
//     * wildcard INADDR_ANY so that the server can get messages from any
//     * of the physical internet connections on this host. (Otherwise we
//     * would limit the server to messages from only one network
//     * interface.)
//     */
//     server.sin_family = AF_INET;         /* Server is in Internet Domain */
//     server.sin_port = 0;                 /* Use any available port      */
//     server.sin_addr.s_addr = INADDR_ANY; /* Server's Internet Address   */

//     if (bind(s, (struct sockaddr *)&server, sizeof(server)) < 0)
//     {
//         perror("bind()");
//         exit(2);
//     }

//     /* Find out what port was really assigned and print it */
//     namelen = sizeof(server);
//     if (getsockname(s, (struct sockaddr *)&server, &namelen) < 0)
//     {
//         perror("getsockname()");
//         exit(3);
//     }

//     printf("Port assigned is %d\n", ntohs(server.sin_port));

//     /*
//     * Receive a message on socket s in buf  of maximum size 32
//     * from a client. Because the last two paramters
//     * are not null, the name of the client will be placed into the
//     * client data structure and the size of the client address will
//     * be placed into client_address_size.
//     */
//     client_address_size = sizeof(client);

//     if (recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr *)&client,
//                  &client_address_size) < 0)
//     {
//         perror("recvfrom()");
//         exit(4);
//     }
//     /*
//     * Print the message and the name of the client.
//     * The domain should be the internet domain (AF_INET).
//     * The port is received in network byte order, so we translate it to
//     * host byte order before printing it.
//     * The internet address is received as 32 bits in network byte order
//     * so we use a utility that converts it to a string printed in
//     * dotted decimal format for readability.
//     */
//     printf("Received message %s from domain %s port %d internet\
//  address %s\n",
//            buf,
//            (client.sin_family == AF_INET ? "AF_INET" : "UNKNOWN"),
//            ntohs(client.sin_port),
//            inet_ntoa(client.sin_addr));

//     /*
//     * Deallocate the socket.
//     */
//     close(s);
// }

// Server program
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 5000
#define MAXLINE 1024
int max(int x, int y)
{
    if (x > y)
        return x;
    else
        return y;
}
int main()
{
    int listenfd, connfd, udpfd, nready, maxfdp1;
    char buffer[MAXLINE];
    pid_t childpid;
    fd_set rset;
    ssize_t n;
    socklen_t len;
    const int on = 1;
    struct sockaddr_in cliaddr, servaddr;
    char *message = "Hello Client";
    void sig_chld(int);

    /* create listening TCP socket */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    // binding server addr structure to listenfd
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 10);

    /* create UDP socket */
    udpfd = socket(AF_INET, SOCK_DGRAM, 0);
    // binding server addr structure to udp sockfd
    bind(udpfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // clear the descriptor set
    FD_ZERO(&rset);

    // get maxfd
    maxfdp1 = max(listenfd, udpfd) + 1;
    for (;;)
    {

        // set listenfd and udpfd in readset
        FD_SET(listenfd, &rset);
        FD_SET(udpfd, &rset);

        // select the ready descriptor
        nready = select(maxfdp1, &rset, NULL, NULL, NULL);

        // if tcp socket is readable then handle
        // it by accepting the connection
        if (FD_ISSET(listenfd, &rset))
        {
            len = sizeof(cliaddr);
            connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
            if ((childpid = fork()) == 0)
            {
                close(listenfd);
                bzero(buffer, sizeof(buffer));
                printf("Message From TCP client: ");
                read(connfd, buffer, sizeof(buffer));
                puts(buffer);
                write(connfd, (const char *)message, sizeof(buffer));
                close(connfd);
                exit(0);
            }
            close(connfd);
        }
        // if udp socket is readable receive the message.
        if (FD_ISSET(udpfd, &rset))
        {
            len = sizeof(cliaddr);
            bzero(buffer, sizeof(buffer));
            printf("\nMessage from UDP client: ");
            n = recvfrom(udpfd, buffer, sizeof(buffer), 0,
                         (struct sockaddr *)&cliaddr, &len);
            printf("New connection, socket fd is %d, ip is : %s, port : %d\n", udpfd,
                   inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
            puts(buffer);
            sendto(udpfd, (const char *)message, sizeof(buffer), 0,
                   (struct sockaddr *)&cliaddr, sizeof(cliaddr));
        }
    }
}
