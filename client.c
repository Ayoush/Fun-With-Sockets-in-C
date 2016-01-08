#include<stdio.h>//for printf and scanf
#include<netinet/in.h>//contains struct sockaddr_in
#include<stdlib.h>//for atoi() function
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>//for close() function
#include<netdb.h>//for getting the host by name
#define MAX_BUFF 1024
void error(char *msg)
{
	perror(msg);
	exit(0);
}
int main(int argc,char *argv[])
{
	int sockif,portno,n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[MAX_BUFF];
	if(argc<3)
	{
		error("uncomplete arguments");
		exit(0);
	}
	portno =atoi(argv[2]);
	sockif=socket(AF_INET,SOCK_STREAM,0);
	if(sockif<0)
	{
		error("unable to open socket");	
	}
	server=gethostbyname(argv[1]);
	if(server==NULL)
	{
		error("no such server exist");
		exit(0);
	}
	bzero((char*)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(portno);
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	if(connect(sockif,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		error("unable to form connection");
	}
	printf("enter the file name");
	bzero(buffer,256);
	scanf("%s",buffer);
	char server_response[256];
	recv(sockif,&server_response,sizeof(server_response),0);
	printf("%s\n",server_response);
	close(sockif);
	return 0;
}


