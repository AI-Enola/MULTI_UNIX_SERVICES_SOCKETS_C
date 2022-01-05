#ifndef CLIENT_H
#define CLIENT_H

int connect_client(void);
void send_to_server(int server_socket, char packet[]);
char* receive_from_server(int server_socket);

#endif /* CLIENT_H */