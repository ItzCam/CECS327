#include "Client.h"

//function to make a request to a server, we need to pass server ip address
char * request( struct Client*new_client, char * server_ip, char *request)
{
    //create an address struct for server 
    struct sockaddr_in server_address;
    
    
    server_address.sin_family = new_client->domain;
    server_address.sin_port = htons(new_client->port);
    server_address.sin_addr.s_addr = (int) new_client->interface;
    
    //we are going to try to make a connection here
    inet_pton(new_client->domain, server_ip, &server_address.sin_addr);
    connect(new_client->socket, (struct sockaddr *)&server_address, sizeof(server_address));
    
    
    //send request to server 
    send(new_client->socket, request,strlen(request), 0);
    
    // read respond from server 
    char * read_res = malloc(2000);
    read(new_client->socket, read_res, 2000 );
    return read_res;
}



struct Client constructor_c(int domain, int service, int tcp, int  port,  size_t interface )
{
    // set the values from our constructor to pass the value to our corresponding attributes  in Client
    struct Client new_client;
    new_client.domain = domain;
    new_client.port = port;
    new_client.interface = interface;
    
    //creat a socket to connect to 
    new_client.socket = socket(domain, service, tcp);
    new_client.request = request;
    return new_client;
}
