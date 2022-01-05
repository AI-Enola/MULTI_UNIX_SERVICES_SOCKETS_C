# MULTI_UNIX_SERVICES_SOCKETS_C

Description : Start server with multiple services, each services will be connected using socket UNIX communication. When a services is connected we will send his ID.
ID's is using to route packet to corresponding services.
Client is connected using AF_INET, each time client send data, ID need to be present in the data frame for the server redirect data to corresponding service.
Service send back data to server and server send data back to client.

Notes : 
Socket Server with multiple services. Each services can be accessible from connected clients.

Services can use another programming languages. (You will need to make a socket file of your prefered programming languages and to link the socket file with your service)

This demo has been tested with one Python as services. Socket and Service test needed to be rewrite in Python. (Python test not present in this Public Demo)

Secure Sockets layer (SSL) is not present in this Public Version.


Tested :

Linux OK

Windows 10 / 11 ( YOU WILL NEED TO CHANGE SOCKET FILES OF THIS PROJECT TO MAKE IT WORK 

Mac OS OK
    
    
 OS Compatibility : macOS & GNU/Linux
 Programming Languages : All with socket available (Tested with Python)
 
 
 DEMO : 
 
 In server repository : 

    gcc -pthread -o server private_socket.c public_socket.c
 
 After that you need to compile the client using : 

    gcc -o user test.c client.c
 
 For each service you will need to compile using : 

    gcc -o service_n service_server.c test_n.c 
 (n = services number ex : gcc -o service_1 service_server.c test_1.c)
 
 
 To start the demo you need to follow these steps : 
 

 1 - START SERVER -  You will need to open a terminal in server repository and to start server : 

    ./server ../services/SERVICE_1/service_1 ../services/SERVICE_2/service_2 ../services/SERVICE_3/service_3

 

 2 - START CLIENT - You will need to open a terminal in client repository and to start client use : 

    ./user
 
 
 Version Public - This project wasn't updated for Public release - Mid 2021 Version

2022-01-05
