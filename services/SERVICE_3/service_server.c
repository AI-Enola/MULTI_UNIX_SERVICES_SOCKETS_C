/*
Author : LA
Description : Socket server for services
Version : Linux / V2.5 / Client - Public

*/

#include "service_server.h" // His Header

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/un.h>

#define SOCKET_NAME "../server/server_vortex.socket" // Filepath
/*
Receive raw_data from socket server as char
Read data
Return : data as char*
Error : Print Error in terminal
*/

char* receive_from_server(int server_socket) {
    static char message[1024];
    memset(message, 0, sizeof(message));

    if (!read(server_socket, message, sizeof(message))) {
        fprintf(stderr, "Error : Receive from server\n");
        exit(EXIT_FAILURE);
    }
    printf("PYKE SERVICE 3 Message received from main server : %s\n", message);
    return message;
}


/*
Get packet send to socket server
If packet then send it
Error : NULL
*/
void send_to_server(int server_socket, char packet[]) {
    if (packet != 0) {
        if (!send(server_socket, packet, strlen(packet), 0)) {
            fprintf(stderr, "Error : Sending to server\n");
            exit(EXIT_FAILURE);
        }
        printf("PYKE SERVICE 3 Message sended to main server : %s\n", packet);
    }
}


/*
Get IP and PORT of the server
Init and create socket client
Connect to socket server
Return : Socket Server ID
Error : Exit code
*/
int connect_client(void) {
    
    struct sockaddr_un serv_addr;
    static unsigned short server_socket = 0;
    static unsigned short main_server = 0;
    
    printf("\nPYKE SERVICE 3 SOCKET C - By LA\nConnecting to socket server...\n");

    // Create new socket
    if ((server_socket = socket(AF_UNIX, SOCK_STREAM, 0)) == 0) {
        perror("PYKE SERVICE 3 Error : Socket creation");
        exit(EXIT_FAILURE);
    }

    // Set the information of the private socket
    serv_addr.sun_family = AF_UNIX;
    strncpy(serv_addr.sun_path, SOCKET_NAME, sizeof(serv_addr.sun_path) - 1);

    if (connect(server_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { // Connect to server
        perror("PYKE SERVICE 3 Error : Connecting to server");
        exit(EXIT_FAILURE);
    }

    send_to_server(server_socket, "2");

    return server_socket;
}