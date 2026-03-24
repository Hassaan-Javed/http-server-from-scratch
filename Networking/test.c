/******************************************************************************
 * Filename:   test.c
 * Author:     Hassaan Javed
 * Date:       11-03-2026
 * Description:
 *   This is a test file
 *
 * Compilation:
 *   gcc test.c -o test
 * Usage:
 *   test.exe
 ******************************************************************************/

#include <stdio.h>
#include <string.h>
#include "Server.h"
#pragma comment(lib, "ws2_32.lib")

void launch(struct Server *server)
{
    int address_length = sizeof(server->address);

    char *hello =
        "HTTP/1.1 200 OK\r\n"
        "Date: Mon, 27 Jul 2809 22:28:53 GMT\r\n"
        "Server: Apache/2.2.14 (Win32)\r\n"
        "Last-Modified: Wed, 22 Jul 2809 19:15:56 GMT\r\n"
//        "Content-Length: 48\r\n" //automatically content length is calculated if this line is commented
        "Content-Type: text/html\r\n"
        "Connection: Closed\r\n"
        "\r\n"
        "<html><body><h1>Hello, World I was written by Hassaan!</h1></body></html>";
    int new_socket;
    char buffer[30000];

    while (1)
    {

        WSADATA wsa;
        WSAStartup(MAKEWORD(2, 2), &wsa);

        printf("========WAITING FOR CONNECTION========\n");

        new_socket = accept(server->socket, (struct sockaddr *)&server->address, (int *)&address_length);

        recv(new_socket, buffer, 30000, 0); // TODO remember this function sepereate from linux

        printf("%s\n", buffer);

        send(new_socket, hello, strlen(hello), 0); // TODO remember this function sepereate from linux

        closesocket(new_socket); // TODO remember this function sepereate from linux
    }

    WSACleanup(); // TODO remember this function sepereate from linux
}
int main(void)
{

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 80, 10, launch);
    server.launch(&server);
    return 0;
}
