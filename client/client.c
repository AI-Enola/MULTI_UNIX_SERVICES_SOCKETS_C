/*
Author : LA
Description : Socket client TEST
Version : Linux / V2 / Client
Public : YES
*/

#include "client.h" // His Header

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 60004


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
    } else {
        printf("\nFrom server : %s\n",message);
    }
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
    struct sockaddr_in serv_addr;
    static unsigned short server_socket = 0; // Init client ID
    
    printf("\nPYKE CLIENT SOCKET C - By LA\nConnecting to socket server...\n");

    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) { // Create new socket
        perror("Error : Socket creation");
        exit(EXIT_FAILURE);
    }
   
    serv_addr.sin_family = AF_INET; // IPV4 INTERNET PROTOCOL
    serv_addr.sin_port = htons(SERVER_PORT); // Port
  
    if(!inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr)) { // Get server IP and apply conversion on it in binary
        perror("Error : Server adress");
        exit(EXIT_FAILURE);
    }

    if (connect(server_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) { // Connect to server
        perror("Error : Connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Client connect to Server -> %s:%d:\n", inet_ntoa(serv_addr.sin_addr), ntohs(serv_addr.sin_port));

    return server_socket;
}