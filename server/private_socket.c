/*
Author : LA
Description : 
    - Private socket used to connect service via local interprocess communication
    - Support for multiples services from one socket

Header : server_socket.h
Version : Linux / V2.5 / Server

Tested :
    - Linux OK
    - Windows 10 NULL
    - Mac OS NULL
Public : YES

Compile : gcc -pthread -o server private_socket.c public_socket.c
CMD : ./server ../services/SERVICE_1/service_1 ../services/SERVICE_2/service_2 ../services/SERVICE_3/service_3
*/

#include "server_socket.h"
#define SOCKET_NAME "server_vortex.socket"

int main(int argc, char *argv[]) { // PRIVATE SOCKET START FIRST BEFORE PUBLIC SOCKET
    struct session service[5]; // 5 SERVICES MAX
    struct sockaddr_un private_server; // UNIX DOMAIN COMMUNICATION
    struct socket private_socket;
    pthread_t stid[5]; // SERVICE THREAD ID
    char command[64];

    printf("PYKE MAIN SERVER SOCKET C - By LA\n\n");

    // CHECK ARGUMENT - NEED MORE ERROR HANDLING
    if ( argc > 6) {
        printf("Too many argument ! \nSyntax: server.c service_1.c service_2.c ...\n");
        exit(EXIT_FAILURE);
    } else if (argc == 1) {
        printf("Socket client need IP and PORT of the server\nSyntax: server.c service_1.c service_2.c ...\n");
        exit(EXIT_FAILURE);
    }

    printf("Creating the private socket...\n");

    // CREATE NEW SOCKET FOR LOCAL INTERPROCESS COMM
    if ((private_socket.server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == 0) {
        perror("Error : Socket creation");
        exit(EXIT_FAILURE);
    }
    unlink(SOCKET_NAME); // Delete old socket - Avoid "address already in use"

    // Set informations of the private socket
    private_server.sun_family = AF_UNIX;
    strncpy(private_server.sun_path, SOCKET_NAME, sizeof(private_server.sun_path) - 1);

    // Assign informations to the socket
    if (bind(private_socket.server_socket, (struct sockaddr *)&private_server, sizeof(private_server)) == -1) {
        perror("Error : Bind server to socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(private_socket.server_socket, 20) == -1) {
        perror("Error : Listen on socket");
        exit(EXIT_FAILURE);
    }

    printf("Waiting for private connections...\n\n");
    
    for (int count = 1; count < argc; count++) { // FOR N ARGUMENT CREATE THREAD TO START SERVICE
        sprintf(command, "%s &", argv[count]);
        system(command); // EXECUTE COMMAND FROM ARGUMENTS

        // ACCEPT INCOMING CONNECTIONS
        if (!(service[count - 1].client_socket = accept(private_socket.server_socket, (struct sockaddr *)&private_server, (socklen_t*)&private_server))) {
            perror("Error : Accepting clients");
            close(private_socket.server_socket);
        }
        receive_from_source(&service[count - 1], service[count - 1].client_socket); // Receiving service ID into buffer
    }
    public_socket(service); // Create and start public socket
    //close(private_socket.server_socket); // USELESS FOR NOW BECAUSE PROGRAM KEEP RUNNING USING PUBLIC_SOCKET FUNCTION
    return 0;
}