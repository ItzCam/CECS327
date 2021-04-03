#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>




#ifndef Client_h
#define Client_h


struct Client
{
    //setting our variables
    int socket;
    int port;
    int log_num;
    int domain;
    int service;
    int tcp;
    size_t interface;
    
    //member method to make request to server
    char *(*request)(struct Client *new_client, char *server_ip, char*request);
    
};

//Overloaded constructor 
struct Client constructor_c(int domain, int service, int protocol, int port, size_t interface);

#endif 





