#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MENU 0
#define BAJA 1
#define ALTA 2
#define TODOS 3
#define ESPECIFICO 4
#define SOLO_ALTA 5
#define ABONAR 6
#define RETIRAR 7
#define BUSCAR_VACIO 8
#define MOSTRAR_LLENA 9
#define MOSTRAR_VACIA 10
#define MOSTRAR_PAISES 11
#define LONGITUDES 12
#define UPD_CLIENTE 13
#define SALIR 14
 
void mostrarMenu();

int main(){
	int i = 0, n = 0, j = 0, m = 0;
	
	struct Pais {
		int id_pais;
		char nombre[20];
	};

	struct Cliente{
		int id_cliente;
		char nombre[20];
		char sexo[2];
		float sueldo;
	};

	struct Sistema{
		struct Pais pais;
		struct Cliente cliente[100];
	};

	printf("Cuantos paises: ");
	scanf("%i", &n);

	struct Sistema Sys[n];

	for (i = 0; i < n; i++){
		getchar();
		Sys[i].pais.id_pais = i;
		printf("Ingresa el nombre del pais [%i]: ", i);
		fgets(Sys[i].pais.nombre, sizeof(Sys[i].pais.nombre), stdin);
		
		char *ptr = strchr(Sys[i].pais.nombre,'\n');
		if(ptr){
			*ptr = '\0';
		}
		
		for (j = 0; j < 100; j++){
			*Sys[i].cliente[j].nombre = '\0';
		}

		
		printf("Ingresa el total de clientes del pais '%s': ", Sys[i].pais.nombre);
			
		m = 0;
		scanf("%i", &m);
		
		getchar();
		for (j = 0; j < m; j++)	{
			
			Sys[i].cliente[j].id_cliente = j;
			printf("\tIngresa el nombre del cliente [%i]: ", j);
			fgets(Sys[i].cliente[j].nombre, sizeof(Sys[i].cliente[j].nombre), stdin	);
			char *ptr = strchr(Sys[i].cliente[j].nombre, '\n');
			if (ptr){
				*ptr = '\0';
			}
		}
	}


	printf("La información de los paises es: \n");
/*	for (i = 0; i < n; i++){
		printf("[%i] - %s\n", Sys[i].pais.id_pais, Sys[i].pais.nombre);

		//size_t m = sizeof(Sys[i].cliente)/sizeof(Sys[i].cliente[0]);
		for(j = 0; j < 100; j++){
			if (*Sys[i].cliente[j].nombre != '\0'){
				printf("Cliente [%i]: %s\n", j, Sys[i].cliente[j].nombre);
			} else
				break;
		}
	}*/

for(i = 0; i < n; i++){
	int temp = 0;
	printf("--> Del país %s, existen ", Sys[i].pais.nombre);
	for (j = 0; j < 100; j++){
		if(*Sys[i].cliente[j].nombre != '\0'){
			temp++;	
		} else 
			break;
	}
	printf("%i clientes\n.", temp);

}

	
	while(1){
		system("clear");
		mostrarMenu();
		int opc;
		scanf("%i", &opc);
		switch(opc){
			case MENU:
			
			break;

			case BAJA:
			
			break;
			case ALTA:
			
			break;
			case TODOS:
			
			break;
			case ESPECIFICO:

			break;
			case SOLO_ALTA:

			break;
			case ABONAR:

			break;
			case RETIRAR:

			break;
			case BUSCAR_VACIO:

			break;
			case MOSTRAR_LLENA:

			break;
			case MOSTRAR_VACIA:

			break;
			case MOSTRAR_PAISES:

			break;
			case LONGITUDES:

			break;
			case UPD_CLIENTE:

			break;
			case SALIR:
				return 0;		
			break;

			default:
				printf("No se reconoció la entrada\n");
				printf("Intentalo de nuevo\n");
				getchar();
			break;


		}
	
	}

	return 0;
}

void mostrarMenu(){
	printf("===== Menu =====\n");
	printf("0. Mostrar Menu\n");
	printf("1. Dar de Alta Cliente\n");
	printf("2. Dar de Baja Cliente\n");
	printf("3. Mostrar todos los clientes\n");
	printf("4. Mostrar cliente en específico\n");
	printf("5. Mostrar solo los clientes dados de alta\n");
	printf("6. Abonar saldo a cliente\n");
	printf("7. Retirar saldo de Cliente\n");
	printf("8. Buscar indice vació en toda la estructura\n");
	printf("9. Mostrar si esta llena la estructura\n");
	printf("10. Mostrar si está toda vacía la estructura\n");
	printf("11. Mostrar nombre de países\n");
	printf("12. Mostrar logitudes\n");
	printf("13. Actualizar datos de cliente en específico\n");
	printf("14. Salir\n");
	printf("------------------\n");
	printf("Elije una opción: \n");
	printf("------------------\n");
}

