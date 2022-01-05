/*
Author : LA
Description : Test socket with sending packets
Version : Linux & Mac OS / V2 / Client
Compile : gcc -o user test.c client.c
Public : YES
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>

#include "client.h"


int main(void) {

    static int server_socket = 0;
    // Connect to socket
    server_socket = connect_client();

    if (!server_socket) {
        exit(EXIT_FAILURE);
    }

    // START DEMO
    send_to_server(server_socket, "<0>Hello, Service 1!<0>");
    receive_from_server(server_socket);

    send_to_server(server_socket, "<0>Hello, Service 2!<1>");
    receive_from_server(server_socket);

    send_to_server(server_socket, "<0>Hello, Service 3!<2>");
    receive_from_server(server_socket);
    
    printf("End of demo.\n");
    // END DEMO

    return 0;
}