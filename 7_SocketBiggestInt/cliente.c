#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define MAX 1000

int main(int argc, char *argv[]){
	if (argc < 2){
		printf("%s <puerto>\n", argv[0]);
		return 1;
	}
	
	char *ip = "127.0.0.1";
	int port = atoi(argv[1]);
	int sock;
	struct sockaddr_in addr;
	socklen_t addr_size;
	char buffer[MAX];
	
	char strA[MAX];
	char strB[MAX];

	printf("Ingresa el numeroA: ");
	scanf("%s", strA);
	
	printf("Ingresa el numeroB: ");
	scanf("%s", strB);

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0){
		perror("[-] Socket del servidor TCP creado.\n");
		return 1;
	}	

	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ip);
	

	connect(sock, (struct sockeaddr*)&addr, sizeof(addr));
	printf("\n[+] Conectado al servidor.\n\n");

	bzero(buffer, MAX);
	strcpy(buffer, strA);
	printf("Cliente A: %s\n", buffer);
	send(sock, buffer, sizeof(buffer), 0);

	bzero(buffer, MAX);
	strcpy(buffer, strB);
	printf("Cliente B: %s\n", buffer);
	send(sock, buffer, sizeof(buffer), 0);

	bzero(buffer, MAX);
	recv(sock, buffer, sizeof(buffer), 0);
	printf("Servidor: %s\n", buffer);

	close(sock);
	printf("\n[+] Desconectado del servidor.\n");	

	return 0;
}
