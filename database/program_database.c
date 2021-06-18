#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 8080

void exitFail(pid_t childID) {
	if(childID < 0) exit(EXIT_FAILURE);
}

void mkdir(char toDir[200]) {
	char *argv[] = {"mkdir", "-p", toDir, NULL};
	execv("/bin/mkdir", argv);
}

int main(int argc, char const *argv[]) {
	int serverFD;
	int newSocket;
	int valread;
	struct sockaddr_in address;
	int x = 0; //opt
	int addrlen = sizeof(address);

	if((serverFD = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		exit(EXIT_FAILURE);
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	if(bind(serverFD, (struct sockaddr *)&address, sizeof(address)) < 0) {
		exit(EXIT_FAILURE);
	}

	if(listen(serverFD, 3) < 0) {
		exit(EXIT_FAILURE);
	}

	while(1) {
		char input[20][300];
		char buff[2048];
		valread = read(newSocket, buff, 2048);

		char *splitInput = strtok(buff, " ");

		int i=0;
		while(splitInput != NULL) {
			strcpy(input[i], splitInput);
			splitInput = strtok(NULL, " ");
			i++;
		}

		int exc_childID = fork();
		exitFail(exc_childID);

		char dbPath[200] = "./databases";

		if(exc_childID == 0) {
			if(strcmp(input[0], "create_db") == 0) {
				strcat(dbPath, "/");
				strcat(dbPath, input[1]);
				mkdir(dbPath);
			}
		}
	}
	return 0;
}