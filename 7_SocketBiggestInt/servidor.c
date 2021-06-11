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

	int sock_servidor, sock_cliente;
	struct sockaddr_in addr_servidor, addr_cliente;
	socklen_t addr_size;
	char buffer[MAX];
	int n;

	sock_servidor = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_servidor < 0) {
		perror("[-] Error al conectar el iniciar el socket");
		return 1;
	}
	printf("[+] Socket del Servidor TCP creado\n");

	memset(&addr_servidor, '\0', sizeof(addr_servidor));
	addr_servidor.sin_family = AF_INET;
	addr_servidor.sin_port = port;
	addr_servidor.sin_addr.s_addr = inet_addr(ip);

	n = bind(sock_servidor, (struct sockaddr*)&addr_servidor, sizeof(addr_servidor));
	listen(sock_servidor, 5);
	printf("Escuchando...\n");

	while(1){
		addr_size = sizeof(addr_cliente);
		sock_cliente = accept(sock_servidor, (struct sockaddr*)&addr_cliente, &addr_size);
		printf("\n[+] Cliente conectado.\n\n");

		bzero(buffer, MAX);
		recv(sock_cliente, buffer, sizeof(buffer), 0);
		printf("Cliente A: %s\n", buffer);

		bzero(buffer, MAX);
		recv(sock_cliente, buffer, sizeof(buffer), 0);
		printf("Cliente B: %s\n", buffer);
		 

		bzero(buffer, MAX);
		strcpy(buffer, "Hola este es el Servidor.");
		printf("Servidor: %s\n", buffer);
		send(sock_cliente, buffer, strlen(buffer), 0);

		close(sock_cliente);
		printf("\n[+] Cliente desconectado.\n\n");

	}
	return 0;
}
