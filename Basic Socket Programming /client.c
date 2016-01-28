#include <stdio.h> //for printf and scanf
#include <netinet/in.h> //struct sockaddr_in
#include <stdlib.h> //for atoi() function
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>//for close() function
#include <netdb.h>//for getting the host by name
#define MAX_BUFF 1024

/*======================for error handling================================*/

void error(char *str)
{
	perror(str);
	exit(1);
}


int main(int argc,char *argv[])
{
	struct sockaddr_in serv_addr;
	int sock,portno,n;
	char *s;
	char buffer[MAX_BUFF];
	int stringlength;
	int bytesrecieved,bytessend;
	struct hostent *server;


	if((argc)<3 || (argc)>4)
	{
		error("Incomplete arguments");
	}

	s=argv[2];//string or message to send;
	server=gethostbyname(argv[1]);
	portno=atoi(argv[3]);

	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		error("unable to open socket");
	}else
	{
		printf("client side socket form\n");
	}

	if(server == NULL)
	{
		error("no server with that name");
	}else
	{
		printf("server found\n");
	}

	bzero((char*)&serv_addr,sizeof(serv_addr));//zero out the strcture
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(portno);
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);

	/*===========================connect ============================*/
	if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	{
		error("unable to setup connection");
	}else
	{
		printf("connection establish\n");
	}


	stringlength=strlen(s);
	if(send(sock,s,stringlength,0)!=stringlength)
	{
		error("not complete string was able to transfer");
	}else
	{
		printf("message send\n");
	}

	int totalbytesreceived=0;
	printf("Received : \n");
	while(totalbytesreceived<stringlength)
	{
		if((bytesrecieved=recv(sock,buffer,MAX_BUFF-1,0))<=0)
		{
			printf("inside is\n");
			error("unable to Receive complete message");
		}else
		{
			
			printf("%d\n",bytesrecieved);
			printf("%s\n",buffer);
		}
		//printf("bytes message %d\n",bytesrecieved);
		totalbytesreceived+=bytesrecieved;
		//buffer[bytesrecieved]='\0';
		printf("%s\n",buffer);
	}
	//printf("\n");
	close(sock);
	exit(0);
}