#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#define SERVICES_MAX 5 // SERVICE THREAD ID - CAN BE CHANGED

#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct session {
    int client_socket;
    char buffer[1024];
};

struct socket {
    int server_socket;
    int option;
    unsigned short socket_number;
};


void receive_from_source(struct session *client, int source);
void send_to_destination(struct session *client, int destination);
int get_service_id(char *id);
void public_socket(struct session service[5]);

#endif /* SERVER_SOCKET_H */