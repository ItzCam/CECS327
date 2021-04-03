#include "Server.h"
#include "Client.h"

//funtion for our server to use for our pthread_create, return void pointer and takes a void pointer arg
void* server_func(void*);

//function for our client will take a char array paramenter 
void client_func(char * );


int main() {



    printf("Welcome to Networking.\n");
	//creating server  using a thread 
	pthread_t server;
	pthread_create(&server, NULL, server_func, NULL);


	
	
	//send communication on the network
	while(1)
	{
	    printf("Type something to the network\n");
	    //create a buffer then clean stack pointer
	    char request[255];
	    memset(request,0,255);
	    fgets(request, 255, stdin);
	    client_func(request);
	    
	}

}



void* server_func(void* args)
{
    printf("Starting server side\n");
	//creating an instance of server, using IPv4(AF_INET) with port 1500 and 10 for backlog 
	struct Server server_side = constructor_s(AF_INET, SOCK_STREAM,0 ,1500,30, INADDR_ANY  );
	
	//cast our socket address to our server adress
	struct sockaddr * address = (struct sockaddr * ) &server_side.address;
	socklen_t address_length = (socklen_t) sizeof(server_side.address);
	
	//need to set infinate loop to connect to our client
	// loop will accept incomming connection, save the connection and then print the connection, close and then wait for another connection 
	while(1)
	{
	   
	    //get connection from client, system call is used with connection-based socket types
	    int client = accept(server_side.socket, address, &address_length);
	    //need to store our request if connection from client is found 
	    char request[255];
	    //we need to make sure we empty out our data from the stack pointer 
	    memset(request, 0, 255);
	    
	    read(client, request, 255);
	    printf("Communicating with client,server IP address: %s\n\tserver says %s\n",inet_ntoa(server_side.address.sin_addr), request);
	    close(client);
	    
	    
	}
	printf("Ending server side\n");
	return NULL;
	
}




void client_func(char * request )
{
    printf("starting client side\n");
    // create an instance of client and then send a message to server 
    struct Client client = constructor_c(AF_INET, SOCK_STREAM, 0, 1500, INADDR_ANY);
    //IP is set to 127.0.0.1 for now...
    client.request(&client, "127.0.0.1",  request);
    printf("Ending Client side\n");
}

