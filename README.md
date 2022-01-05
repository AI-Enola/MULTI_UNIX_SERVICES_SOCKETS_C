# MULTI_UNIX_SERVICES_SOCKETS_C

Tested :
    - Linux OK
    - Windows 10 / 11 ( YOU WILL NEED TO CHANGE SOCKET FILE OF THIS PROJECT TO MAKE IT WORK )
    - Mac OS OK
    
    
 OS Compatibility : macOS & GNU/Linux
 Programming Languages : All with socket available
 
 
 DEMO : 
 
 In server repository : gcc -pthread -o server private_socket.c public_socket.c
 And start with : ./server
 
 After that you need to compile the client using : gcc -o user test.c client.c
 
 For each service you will need to compile using : gcc -o service_n service_server.c test_n.c 
 (n = services number ex : gcc -o service_1 service_server.c test_1.c)
 
 
 Version Public - This project wasn't updated for Public release - Mid 2021 Version
