#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define PORT 8080


int funcSocket();
int commandCreate(int varSocket);

int main(int argc, char const *argv[]) 
{
	struct sockaddr_in address;
	struct sockaddr_in serv_addr;
	int varSocket = 0, valread;

	varSocket = funcSocket();

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) 
	{
		printf("Address invalid, Address not supported\n");
		return -1;
	}

	if(connect(varSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{
		printf("Connection failed\n");
		return -1;
	}

	while(1) 
	{
		char comm[30];
		scanf("%s", comm);

		if(strcmp(comm, "CREATE") == 0) 
		{
			commandCreate(varSocket);
			continue;
		}

		send(varSocket, "failed", strlen("failed"), 0);
	}

	return 0;

}

int funcSocket() 
{
	int varSocket;
	if((varSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Create socket error\n");
		return -1;
	}
	return varSocket;
}

int commandCreate(int varSocket) 
{
	char comm[30];
	char pack[300];
	char db[300];

	scanf("%s", comm);

	if(strcmp(comm, "DATABASE") == 0) 
	{
		scanf("%s", db);
		strcpy(pack, "create_db");
		strcat(pack, db);

		send(varSocket, pack, strlen(pack), 0);
	}

}

