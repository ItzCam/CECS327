#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#ifndef Server_h
#define Server_h




struct Server
{
    //setting our variables
    int socket;
    int port;
    int logs;
    int domain;
    int service;
    struct sockaddr_in address;
    int protocol;
    size_t interface;
};


//overloaded constructor for server
struct Server constructor_s(int domain, int service, int protocol, int port,int logs, size_t interface);

#endif 


