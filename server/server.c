#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <limits.h>
#include <pthread.h>

#define SERVERPORT 8989
#define BUFSIZE 4096
#define SOCKETERROR (-1)
#define SERVER_BACKLOG 100

typedef struct sockaddr_in SA_IN;
typedef struct sockaddr SA;

void * handle_connection(void* p_client_socket);
int check(int exp, const char* msg);

int main(int argc, char** argv){
	int server_socket, client_socket, addr_size;
	SA_IN server_addr, client_addr;

	check((server_socket = socket(AF_INET, SOCK_STREAM, 0)),
		"Failed to create socket");

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(SERVERPORT);

	check(bind(server_socket, (SA*)&server_addr, sizeof(server_addr)),
		"Bind failed!");

	check(listen(server_socket, SERVER_BACKLOG),
			"Listen failed!");

	while(true){
		printf("waiting for connections .... \n");
		// wait, and eventually accept an incoming connection
		check(client_socket = (accept(server_socket, (SA*)&client_addr, (socklen_t*)&addr_size)),
			"accept failed!");

		printf("Connected!\n");

		pthread_t t;
		int *pclient = malloc(sizeof(int));
		*pclient = client_socket;
		pthread_create(&t, NULL, handle_connection, pclient);
	}

	return 0;
}

int check(int exp, const char *msg){
	if(exp == SOCKETERROR){
		perror(msg);
		exit(1);
	}

	return exp;
}

void *handle_connection(void* p_client_socket){
	int client_socket = *((int *)p_client_socket);
	free(p_client_socket);
	char buffer[BUFSIZE];
	size_t bytes_read;
	int msgsize = 0;
	char actualpath[PATH_MAX + 1];

	// read the client's message -- the name of the file to read
	while((bytes_read = read(client_socket, buffer + msgsize, sizeof(buffer) - msgsize - 1)) > 0){
		msgsize += bytes_read;
		if(msgsize > BUFSIZE - 1 || buffer[msgsize - 1] == '\n') break;
	}

	check(bytes_read, "recv error");
	buffer[msgsize - 1] = 0;

	printf("REQUEST ::  %s\n", buffer);
	fflush(stdout);

	// validity check
	if(realpath(buffer, actualpath) == NULL){
		printf("ERROR(bad path) :: %s\n", buffer);
		close(client_socket);
		return NULL;
	}

	FILE *fp = fopen(actualpath, "r");
	if(fp == NULL){
		printf("Error(open) :: %s\n",buffer);
		close(client_socket);
		return NULL;
	}

	while((bytes_read = fread(buffer, 1 , BUFSIZE, fp)) > 0){
		printf("sending %zu bytes\n", bytes_read);
		write(client_socket, buffer, bytes_read);
	}

	close(client_socket);
	fclose(fp);
	printf("closing connection!\n");

	return NULL;
}
