/******************************************************************************
 * Filename:   Server.c
 * Author:     Hassaan Javed
 * Date:       11-03-2026
 * Description:
 *   This is a starting template for a C program.
 *   Includes standard headers and main function structure.
 *   You can extend this template for any project.
 *
 * Compilation:
 *   gcc Server.c -o Server
 * Usage:
 *   Server.exe
 ******************************************************************************/

#include <winsock2.h>
#include "Server.h"
#include <stdio.h>

#pragma comment(lib, "ws2_32.lib")

struct Server server_constructor(int domain, int service, int protocol, u_long mInterface, int port, int backlog, void (*launch)(struct Server *server))
{
    //must call this before binding a connection 
    //very important
    WSADATA wsa;
    int startup_done = WSAStartup(MAKEWORD(2, 2), &wsa);

    struct Server server;

    server.domain = domain;
    server.service = service;
    server.mInterface = mInterface;
    server.backlog = backlog;
    server.port = port;

    server.address.sin_family = domain;

    server.address.sin_port = htons(port);

    server.address.sin_addr.S_un.S_addr = htons(mInterface);

    server.socket = socket(domain, service, protocol);

    if (server.socket == 0)
    {
        
        perror("Failed to connect the socket...\n");
        exit(1);
    }

    if (bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
    {

        perror("Failed to bind");
        exit(1);
    }

    if (listen(server.socket, server.backlog) < 0)
    {
        perror("Failed to listen to server...\n");
        exit(1);
    };

    server.launch = launch;

    return server;
}