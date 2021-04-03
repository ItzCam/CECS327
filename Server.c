 #include "Server.h"


//defining our overloaded constructor 
struct Server constructor_s( int domain , int service , int protocol, int  port, int logs, size_t interface )
{
    // set the values from our constructor to pass the value to our corresponding attributes  in Server
    struct Server new_server;
    new_server.domain = domain;
    new_server.service = service;
    new_server.protocol = protocol;
    new_server.port = port;
    new_server.interface = interface;
    new_server.logs = logs;
    
    //manipulate our attributes to be used in network bytes rather than original datatype
    new_server.address.sin_family = domain;
    new_server.address.sin_port = htons(port);
    new_server.address.sin_addr.s_addr = htonl(interface);
    
    //now we can create a socket for our data to communicate across the network
    new_server.socket = socket(domain, service, protocol);
    
    //check for errors 
    
    //connection fails 
    if(new_server.socket == 0)
    {
        perror("Unable to connect socket, try again.\n");
        exit(1);
    }
    
    //if fail to bind our socket to the network
    if((bind(new_server.socket, (struct sockaddr *) & new_server.address, sizeof(new_server.address))) < 0 )
    {
        perror("Fail to bind socket to network, try again\n");
        exit(2);
    }
    
    
    //if fail to listen incomming connections 
    if((listen(new_server.socket, new_server.logs)) < 0)
    {
        perror("Fail to accept incomming communitation. try again\n ");
        exit(3);
    }
    
    return new_server;

}
