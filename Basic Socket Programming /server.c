#include <stdio.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>

#define MAXPENDING 5
#define RCVBUFFER 1024
void error(char *msg)
{
	perror(msg);
	exit(1);
}

void HandleClient(int clientsock)
{
	char buffer[RCVBUFFER];
	int rcvmessage;
	if((rcvmessage = recv(clientsock,buffer,RCVBUFFER,0))< 0)
	{
		error("not receiving anything");
	}
	else
	{
		printf("rcv message %d\n",rcvmessage);
		printf("%s\n",buffer);
	}


	while (1) {
      int read = recv(clientsock, buffer, RCVBUFFER, 0);

      if (!read) break; // done reading
      if (read < 0) error("Client read failed\n");
      int err;
      err = send(clientsock, buffer, read, 0);
      if (err < 0) error("Client write failed\n");
    }
	close(clientsock);
}

int main(int argc,char *argv[])
{
	int serverSock;
	int clientSock;
	struct sockaddr_in server;
	struct sockaddr_in client;
	int serverPort;
	unsigned int clientLen;

	if(argc!=2)
	{
		error("Incomplete Arguments");
	}	

	serverPort=atoi(argv[1]);
	if((serverSock=socket(AF_INET,SOCK_STREAM,0))<0)	
	{
		error("unable to open socket for incoming connection");
	}else
	{
		printf("server side sock open\n");
	}	
	memset(&server,0,sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(serverPort);
	server.sin_addr.s_addr=INADDR_ANY;

	if(bind(serverSock,(struct sockaddr *)&server,sizeof(server))<0)
	{
		error("unable to bind the server");
	}else
	{
		printf("binding establish\n");
	}	

	if(listen(serverSock,MAXPENDING)<0)
	{
		error("listen fail");
	}else
	{
		printf("listening\n");
	}

	while(1)
	{
		clientLen=sizeof(client);
		if((clientSock = accept(serverSock,(struct sockaddr *	)&client,&clientLen))<0)
		{
			error("unable to connect in server");
		}
		printf("Handling client %s\n", inet_ntoa(client.sin_addr));
		HandleClient(clientSock);
	}	
	return 0;
}