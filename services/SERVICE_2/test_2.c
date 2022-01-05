/*
Author : LA
Description : Test socket with sending packets
Version : Linux / V2.5 / Service
Compile : gcc -o service_2  service_server.c
Public : YES
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "service_server.h"


int main(void) {

    static int server_socket = 0;

    // Connect to socket
    server_socket = connect_client();

    if (!server_socket) {
        exit(EXIT_FAILURE);
    }
    
    printf("Packet from client : %s.\n\n", receive_from_server(server_socket));

    send_to_server(server_socket, "Hello, Client! From Service 2");
    
    return 0;
}