#include<stdio.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<fcntl.h>
#include<netdb.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
void error(char *msg)
{
	printf("%s\n",msg);
	exit(0);
	
}
int main()
{
	struct sockaddr_in server_sock;
	int sockfd,portno;
	portno=8080;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		error("error creating socket");
	}
	printf("Socket created\n");
	server_sock.sin_family=AF_INET;
	server_sock.sin_port=htons(portno);
	server_sock.sin_addr.s_addr=INADDR_ANY;
	bind(sockfd,(struct sockaddr*)&server_sock,sizeof(server_sock));
	listen(sockfd,5);
	char server_response[256]="yes you have reached the server";
	int client_socket;
	client_socket=accept(sockfd,NULL,NULL);
	send(client_socket,server_response,sizeof(server_response),0);
	close(sockfd);
	return 0;
}

