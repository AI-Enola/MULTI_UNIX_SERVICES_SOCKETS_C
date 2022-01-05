# MULTI_UNIX_SERVICES_SOCKETS_C

Tested :
    - Linux OK
    - Windows 10 / 11 ( YOU WILL NEED TO CHANGE SOCKET FILE OF THIS PROJECT TO MAKE IT WORK )
    - Mac OS OK
    
    
 OS Compatibility : macOS & GNU/Linux
 Programming Languages : All with socket available (Tested with Python)
 
 
 DEMO : 
 
 In server repository : gcc -pthread -o server private_socket.c public_socket.c
 
 After that you need to compile the client using : gcc -o user test.c client.c
 
 For each service you will need to compile using : gcc -o service_n service_server.c test_n.c 
 (n = services number ex : gcc -o service_1 service_server.c test_1.c)
 
 
 To start the demo : 
 
 1 - START SERVER -  You will need to open a terminal in server repository and to start server : ./server ../services/SERVICE_1/service_1 ../services/SERVICE_2/service_2 ../services/SERVICE_3/service_3
 Note : Server start services
 
 2 - START CLIENT - You will need to open a terminal in client repository and to start client use : ./user
 
 
 Version Public - This project wasn't updated for Public release - Mid 2021 Version
 2022-01-05
