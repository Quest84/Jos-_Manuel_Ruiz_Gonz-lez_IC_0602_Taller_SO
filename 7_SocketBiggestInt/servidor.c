#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#define MAX 1000

int* GetBigInteger(char str[MAX], int arr[MAX]);
void imprimir(int size, int *p);
int* suma(int *p, int *q, int *pSuma, int sizeA, int sizeB);
char *PutBigInteger(int arr[MAX], char str[MAX], int size);

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

	if (bind(sock_servidor, (struct sockaddr*)&addr_servidor, sizeof(addr_servidor)) == - 1){
		printf("\nError en bind(?)\n");
		return -1;
	}

	listen(sock_servidor, 5);
	printf("Escuchando...\n");

	char strA[MAX];
	char strB[MAX];
	int arrA[MAX];
	int arrB[MAX];
	int arrSuma[MAX] = {0};

	while(1){
		addr_size = sizeof(addr_cliente);
		sock_cliente = accept(sock_servidor,(struct sockaddr*)&addr_cliente, &addr_size);
		printf("\n[+] Cliente conectado.\n\n");
	
		// Recibe el primer arreglo
		bzero(buffer, MAX);
		recv(sock_cliente, buffer, sizeof(buffer), 0);
		printf("--> Cliente ha mandado el numero A: %s\n", buffer);
		
		// Copia el buffer en la Arreglo A
		strcpy(strA, buffer);
		int sizeA = (unsigned)strlen(strA);
		// printf("strA = %s\n", strA);

		// Recibe el segundo arreglo
		bzero(buffer, MAX);
		recv(sock_cliente, buffer, sizeof(buffer), 0);
		printf("--> Cliente ha mandado el numero B: %s\n", buffer);
		
	        // Copia el buffer en el Arreglo B
		strcpy(strB, buffer);	
		int sizeB = (unsigned)strlen(strB);
		// printf("strB = %s\n", strB);

		int *p, *q;
		int *pSuma = arrSuma;
	
		p = GetBigInteger(strA, arrA);
		q = GetBigInteger(strB, arrB);

		// Los arreglos se suman, los valores se intecambian dependiendo el tamaño
		if (sizeA <= sizeB)
			pSuma = suma(q, p, arrSuma, sizeB, sizeA);
		else
			pSuma = suma(p, q, arrSuma, sizeA, sizeB);	

		bzero(buffer, MAX);
		char *b = buffer;
		// El arreglo suma se copia al buffer
		// imprimir(sizeA, pSuma);
		// imprimir(sizeA, p);
		// imprimir(sizeB, q);
		b =  PutBigInteger(pSuma, buffer, sizeA);
		printf("Servidor responde con la suma de A + B =  %s\n", b);
		send(sock_cliente, buffer, strlen(buffer), 0);

		close(sock_cliente);
		printf("\n[+] Cliente desconectado.\n\n");

	}
	return 0;
}

int *suma(int *p, int *q, int arrSuma[MAX], int sizeA, int sizeB){
	// p es el puntero al arreglo más grande y sizeA el tamaño de este
	printf("\n--> El numero mayor es: ");
		imprimir(sizeA, p);
	printf("--> El numero menor es: ");
		imprimir(sizeB, q);

	
	int temp = 0;
	int carry = 0;
	int j = sizeB - 1;
	for (int i = sizeA - 1; i >= 0; i--){
		temp = carry + (p[i] + q[j]);
		if (temp >= 10){
			carry = temp/10;
			temp = temp%10;
		} else {
			carry = 0;
		}
		j--;
		arrSuma[i] = temp;
	}
	if (carry != 0){
		arrSuma[0] = arrSuma[0]+(carry*10);
	}


	return arrSuma;
}

void imprimir(int size, int *p){
	for (int i = 0; i < size; i++){
		printf("%i", *(p + i));
	}
	printf(" <-- int[]\n");
}

int* GetBigInteger(char str[MAX], int arr[MAX]){
	int x = (unsigned)strlen(str);
	printf("\n--> El tamaño de tu numero es de %d digitos", x);
	printf("\n--> Tu numero es %s <-- char[]\n", str);

	int i = 0;
	while (i != x){
		// Extrayendo los números del arreglo de caracteres
		// str[a] - '0'
		// = ASCII(str[a]) - ASCII('0')
		// = ASCII(str[a]) - 48
		arr[i] = str[i] - '0';
		i++;
	}

	return arr;
}

char *PutBigInteger(int arr[MAX], char str[MAX], int size){
	// Buscar una forma para determinar la longitud de int pSuma[] 
	// int x = sizeof(arr)/sizeof(*arr);
	int i = 0;
	int j = 0;
	// printf("\nPrimer elemento +10 = %i", arr[i]+'0');
	if ((arr[i]) >= 10){
		int temp2 = arr[i];
		str[0] = (temp2/10) + '0';
		// printf("\n%c", str[i]);	
		str[1] = (temp2%10) + '0';
		// printf("\n%c", str[i]);	
		size++;
		i = i + 2;
		j++;
	}
	// printf("\nLongitud del arreglo pSuma = %d\n", size);
	// printf("\ni = %d\n", i);
	while(i != size){
		// Agregando los números del arreglo de enteros al arreglo de caracteres
		// str[a] + '0'
		str[i] = arr[j] + '0';
		// printf("\n%c", str[i]);	
		i++;
		j++;
	}
	return str;
}
