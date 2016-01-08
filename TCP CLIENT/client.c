#include<stdio.h>//for using printf and scanf function
#include<stdlib.h>//for using atoi() function
#include<sys/types.h>			
#include<sys/socket.h>//API conatins function like connect socket send rev
#include<netinet/in.h>//contains the structure sockaddr_in
#include<string.h>//for memset
#include<fcntl.h>
#include<netdb.h>//for using structure hostnet and for getting the host by name 
#define MAX_BUFF 1024

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int main(void)//command line arguments portno address its port no for example (12535 localhost 12545)
{
	int network_socket,portno,n;
	struct sockaddr_in server_address;
	network_socket=socket(AF_INET,SOCK_STREAM,0);//creates a end point or socket through which we communicate 
	if(network_socket<0)
	{
		error("unable to open socket");
	}
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr=INADDR_ANY;//for connnecting to 0.0.0.0
	int connection_status = connect(network_socket,(struct sockaddr*) &server_address,sizeof(server_address));
	if(connection_status == -1)
	{
		error("connection cannot be establis");
	}
	//recieve the data
	char server_response[256];
	recv(network_socket,&server_response,sizeof(server_response),0);
		
	printf("%s\n",server_response);
	close(network_socket);
	return 0;
}


