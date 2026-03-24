/******************************************************************************
 * Filename:   Server.c
 * Author:     Hassaan Javed
 * Date:       11-03-2026
 * Description:
 *   This is the server file
 *
 * Compilation:
 *   gcc Server.c -o Server
 * Usage:
 *   Server.exe
 ******************************************************************************/
#ifndef Server_h
#define Server_h

#include <winsock2.h> //Alternative for sys/socket and netinet/in


struct Server
{
    int domain;
    int service;
    int protocol;
    u_long mInterface;
    struct sockaddr_in address;

    int port;
    int backlog;

    SOCKET socket;
    void (*launch)(struct Server *server);


};

struct Server server_constructor(int domain, int service, int protocol, u_long mInterface, int port, int backlog, void (*launch)(struct Server *server));

#endif
