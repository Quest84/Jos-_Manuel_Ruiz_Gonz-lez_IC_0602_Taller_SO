#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#include "debug.h"
#define MAX 1000


int main(int argc, char *argv[]){
	if (argc < 3){
		printf("%s <puerto> <ip>\n", argv[0]);
		return 1;
	}
	
	char ip[(strlen(argv[2]))];
	strcpy(ip, argv[2]);
	
	int port = atoi(argv[1]);
	int sock;
	struct sockaddr_in addr;
	char buffer[MAX];
	
	char strA[MAX];
	char strB[MAX];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == 1){
		printf("[-] Error al establecer la conexión\n");
		return -1;
	}	
	
	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ip);

	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1){
		printf("\n[-] Error al conectar con el servidor\n\n"); 
		return -1;
	} else {
		printf("\n[+] Conectado al servidor.\n\n");
		//debug(sock);
	}
	
	// Primero conecta con el servidor y después pide los númermos
	printf("Ingresa el numero A: ");
	scanf("%s", strA);
	
	printf("Ingresa el numero B: ");
	scanf("%s", strB);

		
	bzero(buffer, MAX);
	strcpy(buffer, strA);
	printf("\n--> Cliente ha enviado al Servidor el número A: %s", buffer);
	send(sock, buffer, sizeof(buffer), 0);

	bzero(buffer, MAX);
	strcpy(buffer, strB);
	printf("\n--> Cliente ha enviado al Servidor el número B: %s\n", buffer);
	send(sock, buffer, sizeof(buffer), 0);

	bzero(buffer, MAX);
	recv(sock, buffer, sizeof(buffer), 0);
	printf("\nEl Servidor respondió al Cliente con la suma:  %s\n", buffer);
	
	close(sock);
	printf("\n[+] Desconectado del servidor.\n");	

	return 0;
}
