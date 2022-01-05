/*
Author : LA
Description : 
    - Public socket used to connect client via IPV4 INTERNET Protocol using TCP

SSL : Available on dev version
Header : server_socket.h
Version : Linux / V2.5 / Server

Tested :
    - Linux OK
    - Windows 10 / 11 ( YOU WILL NEED TO CHANGE SOCKET FILE OF THIS PROJECT TO MAKE IT WORK )
    - Mac OS OK


Public : YES
NOTE : NOT UPDATED - MID 2021 VERSION
*/



// PROJECT LIBRARY
#include "server_socket.h"
#define PUBLIC_IP "127.0.0.1"
#define PUBLIC_PORT 60004 // PORT - CAN BE CHANGED
#define CLIENT_MAX 10


struct session service_data[SERVICES_MAX]; // NOT SUPPOSED TO BE GLOBAL


// RECEIVE DATA FROM CLIENT
void receive_from_source(struct session *client, int source) {

    printf("\n\nReceiving packet from source...\n");
    memset(client->buffer, 0, sizeof(client->buffer));

    if (!read(source, client->buffer, 1024)) {
        fprintf(stderr, "Error : Receive from source\n");
        pthread_exit(0); // EXIT THREAD WHEN ERROR OCCUR - CLIENT DISCONNECTED TO SERVER
    }

    printf("Source: %d | Packet: %s\n\n", source, client->buffer);
}


// SEND DATA TO CLIENT
void send_to_destination(struct session *client, int destination) {

    printf("\n\nSending packet to destination...\n");

    if (!send(destination, client->buffer, strlen(client->buffer), 0)) {
        fprintf(stderr, "Error : Sending to destination");
        pthread_exit(0); // EXIT THREAD WHEN ERROR OCCUR - CLIENT DISCONNECTED TO SERVER
    }

    printf("Destination: %d | Packet: %s\n\n", destination, client->buffer);
}


int get_service_id(char *id) { // Check service ID into packet ex : <0>Hello,World!<3> 3 is service ID
    
    static char tmp[8]; // SERVICE ID

    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, &id[strlen(id) - 2]);

    // Browse through services array to check service ID match
    for (int count = 0; count < sizeof(service_data) / sizeof(service_data[0]); count++) {
        
        if (atoi(service_data[count].buffer) == atoi(tmp)) {
            printf("Associating client service ID with corresponding service.\n"); // IF client push 0 as service ID and if it match with service then return corresponding socket to send data to the service
            return service_data[count].client_socket;
        }
    }
}


// SESSION FOR EACH SERVICE - START DEMO - To use this project you will need to work in this function
void *session(void *args) {
    
    struct session *client = args; // GET CLIENT DATA INTO CLIENT STRUCT
    
    int service_socket;
    

    // DEMO START HERE
    for (int count = 3; count > 0; count--) {

        receive_from_source(client, client->client_socket); // Receive data from client

        service_socket = get_service_id(client->buffer); // Check packet service id

        send_to_destination(client, service_socket); // Send data from client to service
        
        receive_from_source(client, service_socket); // Receiving from service
        
        send_to_destination(client, client->client_socket); // Send data from service to client
    }
    printf("EXITING DEMO...\n");
    
    exit(EXIT_SUCCESS);
    // DEMO END HERE
}


// CREATE PUBLIC SOCKET FOR IPV4 TCP
void public_socket(struct session service[SERVICES_MAX]) {

    struct sockaddr_in public_server;
    struct session client[CLIENT_MAX]; // SET CLIENT MAX
    struct socket public_socket;

    pthread_t tid[CLIENT_MAX]; // MAX THREAD

    public_socket.socket_number = 0;

    for (int count = 0; count != SERVICES_MAX; count++) {
        service_data[count] = service[count]; // ADD STRUCT OF DATA INTO GLOBAL STRUCT - NOT SUPPOSED TO USE GLOBAL STRUCT
    }

    printf("\n\nCreating the public socket...\n");

    if ((public_socket.server_socket = socket(AF_INET, SOCK_STREAM, 0)) == 0) { // CREATE NEW SOCKET AS IPV4 INTERNET TCP
        perror("Error : Socket creation");
        exit(EXIT_FAILURE);
    }

    // Set options for the socket - Reuse ip addr and port to avoid "address already in use" 
    if (setsockopt(public_socket.server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &public_socket.option, sizeof(public_socket.option))) {
        perror("Error : Setting socket options");
        exit(EXIT_FAILURE);
    }

    // Set informations of the server socket
    public_server.sin_family = AF_INET; // IPV4 INTERNET PROTOCOL
    
    public_server.sin_addr.s_addr = inet_addr(PUBLIC_IP); // IPV4 ADDRESS OF THE SOCKET
    
    public_server.sin_port = htons(PUBLIC_PORT); // PORT OF THE SOCKET
    
    // Assign informations to the socket
    if (bind(public_socket.server_socket, (struct sockaddr *)&public_server, sizeof(public_server)) > 0) {
        perror("Error : Bind server to socket");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(public_socket.server_socket, 5) == -1) { // CHECK LISTEN __n
    perror("Error : Listen on socket");
    exit(EXIT_FAILURE);
    }

    printf("Socket: %s:%d\n", inet_ntoa(public_server.sin_addr), ntohs(public_server.sin_port)); // PRINT IPV4 ADDRESS AND PORT OF SERVER
    
    printf("Waiting for public connections...\n\n");

    while (1) { // KEEP RUNNING THE PROGRAM
    
        // ACCEPT INCOMING CONNECTIONS
        if (!(client[public_socket.socket_number].client_socket = accept(public_socket.server_socket, (struct sockaddr *)&public_server, (socklen_t*)&public_server))) {
            perror("Error : Accepting clients");
            close(public_socket.server_socket);
        }

        // GET IPV4 AND PORT OF ACCEPTED CLIENT
        if (!(getpeername(public_socket.server_socket, (struct sockaddr *)&public_server, (socklen_t*)&public_server))) {
            perror("Error : getpeername");
        }

        printf("Client: %s:%d:%d\n", inet_ntoa(public_server.sin_addr), ntohs(public_server.sin_port), client[public_socket.socket_number].client_socket); // CLIENT INFO
        printf("Creating thread number %d for client %d\n",public_socket.socket_number, client[public_socket.socket_number].client_socket);

        if (pthread_create(&tid[public_socket.socket_number], 0, session, &client[public_socket.socket_number]) != 0) { // CREATE THREAD FOR CLIENT
            perror("Error : gpthread_create");
        }

        public_socket.socket_number++; // INCREMENT THREAD ID
    }
    
}
