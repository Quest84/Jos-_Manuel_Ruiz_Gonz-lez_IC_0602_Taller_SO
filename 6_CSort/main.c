/* Hacer un programa en C, que:
 *  -> Reciba 2 argumentos en línea de comandos, que son nombres de archivos
 *  -> El 1er arg es una archivo de entrada y el 2do arg es el nombre de un arch de salida
 *  -> El programa va a abrir el primer archivo (no mayor a 4 o 5K) que contendrá un texto ASCII
 *  -> Leerá el archivo y ordenará las palabras alfabéticamente en una lista enlazada
 *  -> Luego pasará el comienzo de esa lista a una función, que grabará las palabras en el archvo de salida
 *  -> Con control de errores
 */

#include<stdio.h>
#include<string.h>

#define TAM_NOMBRE 100
#define TAM_NUMEROS 100000

int existe_archivo(char *nombre_arch);
int crear_archivo(char *nombre_arch);
void cerrar_archivo(FILE *ptrArchivo, char *nombre_arch);
FILE *abrir_Archivo_lectura_escritura(char *nombre_arch);
int tiene_datos_arch(char *nombre_arch);
FILE *abrir_Archivo_solo_Lectura(char *nombre_arch);
void imprimir_vector(int vector[], int tam);
void ordBurbuja(int a[], int n);
int total_numeros_Arch(char *nombre_arch);
void burbuja(char arreglo[][TAM_NOMBRE], int longitud);

int main(int argc, char *argv[]){
	FILE *inputFile = NULL;
	FILE *outputFile = NULL;
	
	char inputNombre[TAM_NOMBRE];
	char outputNombre[TAM_NOMBRE];
	int contador = 0;
	char str_archivo[20];
	int existe_arch = 0;	

	if (argc > 2 && argc <= 3){
		strcpy(inputNombre, argv[1]);
		strcpy(outputNombre, argv[2]);
		printf("----Leyendo argumentos----\n");
		printf("Cantidad de argumentos: %i\n", argc);
		printf("bin = %s\n", argv[0]);
		printf("Argumento 1: %s\n", inputNombre);
		printf("Argumento 2: %s\n", outputNombre);
	} else{
		printf("¡Te olvidaste de los argumentos!\n");
		printf("Agrega dos argumentos antes de la ejecución del programa!\n");
		printf("\t-> Primer argumento - Archivo a Leer\n");
		printf("\t\t-> Segundo argumento - Archivo a Escribir!\n");

		return -1;
	}
	
	printf("\n------------------------------------------------");
	printf("\nVerificando si existe el archivo de entrada...");
	printf("\n------------------------------------------------\n");
	existe_arch = existe_archivo(inputNombre);
	if (existe_arch){
		printf("\n%s existe", inputNombre);
	} else{
		printf("\n%s no existe\n", inputNombre);
		printf("\nSe creará el archivo...\n");
		if(crear_archivo(inputNombre)){		
			printf("\n-----------------------------------------");
			printf("\nEl archivo %s ha sido creado", inputNombre);
			printf("\n-----------------------------------------");
			printf("\nLlena el archivo con un parrafo de texto para que pueda continuar el programa");
			printf("\nDespués pasa el mismo archivo como parámetro al ejecutar el programa\n");
			
			return -1;
		} else {
			printf("\n-----------------------------------------");
			printf("\nEl archivo %s no pudo crearse", inputNombre);
			printf("\n-----------------------------------------");

		}
		return -1;
	}

	if(tiene_datos_arch(inputNombre)){
		printf("\n-----------------------------------------");
		printf("\t\nEl archivo %s contiene datos", inputNombre);
		printf("\n-----------------------------------------");
		printf("\n\n----------Lectura del Archivo------------\n");

		inputFile = abrir_Archivo_solo_Lectura(inputNombre);
		if (inputFile == NULL){
			printf("\n-----------------------------------------");
			printf("\nEl archivo %s no pudo abrirse", inputNombre);
			printf("\n-----------------------------------------");
		} else {
			printf("\n-----------------------------------------");
			printf("\nEl archivo %s ha sido abiero", inputNombre);
			printf("\n-----------------------------------------\n");
			fscanf(inputFile, "%s", str_archivo);
			while(!feof(inputFile)){
				printf("%d. %s\n",contador, str_archivo);
				fscanf(inputFile, "%s", str_archivo);
				contador++;
			}
			printf("\nTotal de palabras leídas: %d\n", contador);
			// BUG 1. No se por qué se rompe si el tamaño del arreglo de arreglos es de 27
			char palabrasCrudas[contador+1][TAM_NOMBRE];
			// Pasando las palabras a un arreglo
			// fscanf(inputFile, "%s", str_archivo);
			// printf("\nFunciona? %s", str_archivo);
			cerrar_archivo(inputFile, inputNombre);
			
			// Nosequeestoyhaciendo
			inputFile = abrir_Archivo_solo_Lectura(inputNombre);
			contador = 0;
			fscanf(inputFile, "%s", str_archivo);
			memcpy(palabrasCrudas[contador], str_archivo, TAM_NOMBRE);
			// printf("%d. %s\n", contador, str_archivo);
			while(!feof(inputFile)){
				contador++;
				fscanf(inputFile, "%s", str_archivo);
				memcpy(palabrasCrudas[contador], str_archivo, TAM_NOMBRE);
				// printf("%d. %s\n", contador, str_archivo);
			}
			// printf("\nFunciona? - > %d, %s\n", contador, palabrasCrudas[contador]);
			cerrar_archivo(inputFile, inputNombre);

			// int longitud = sizeof(palabrasCrudas) / sizeof(palabrasCrudas[0]);

			printf("\nImprimiendo arreglo sin ordenar\n");
			int i;
			for (i = 0; i < contador; i++){
				printf("%d.  %s\n", i, palabrasCrudas[i]);
			}

			// Ordenando el arreglo
			burbuja(palabrasCrudas, contador);

			printf("\nImprimirendo arreglo ordenado\n");
			for (i = 0; i < contador; i++){
				printf("%d. %s\n", i, palabrasCrudas[i]);
			}
		}

	} else {
		printf("\n-----------------------------------------");
		printf("\t\nEl archivo %s no contiene datos", inputNombre);
		printf("\n-----------------------------------------");
		return -1;
	}
		

	return 0;
}


void burbuja(char arreglo[][TAM_NOMBRE], int longitud){
	// Arreglo temporal para el intercamio de las cadenas
	char temporal[TAM_NOMBRE];

	int i, iActual;
	for (i = 0; i < longitud; i++){
		for (iActual = 0; iActual < longitud - 1; iActual++){
			int iSig = iActual + 1;

			// Si la cadena es mayor que la siguiente (alfabeticamente) entonces intercambian
			if (strcmp(arreglo[iActual], arreglo[iSig]) > 0){
				// Mueve la cadena actual a a temporal
				memcpy(temporal, arreglo[iActual], TAM_NOMBRE);
				// Mueve al actual el siguiente elemento
				memcpy(arreglo[iActual], arreglo[iSig], TAM_NOMBRE);
				// El siguiente elemento, lo que había antes en el actual ahora está en el temporal
				memcpy(arreglo[iSig], temporal, TAM_NOMBRE);
			}
		}
	}
	// No se devuelve anda
}

int total_numeros_Arch(char *nombre_arch){
        int lee_linea = 0, contador = 0;
        FILE *ptrArchivo;
        ptrArchivo = abrir_Archivo_solo_Lectura(nombre_arch);
        if(ptrArchivo == NULL){
                printf("El archivo -> %s <- NO se pudo abrir desde total_numeros().\n", nombre_arch);
        }
        else{
                printf("Archivo -> %s <- abierto desde total_numeros().\n", nombre_arch);
                // leo si hay datos
                fscanf(ptrArchivo, "%d", &lee_linea);
                // mientras no sea fin de archivo.
                while(!feof(ptrArchivo)){
                        contador++;
                        // leo si hay datos
                        fscanf(ptrArchivo, "%d", &lee_linea);
                }
                cerrar_archivo(ptrArchivo, nombre_arch);
        }
        return contador;
}

int tiene_datos_arch(char *nombre_arch){
        int hay_Datos = 0;
        FILE *ptrArchivo;
        int lee_linea = 0, contador = 0;
        ptrArchivo = abrir_Archivo_solo_Lectura(nombre_arch);
        if(ptrArchivo == NULL){
                printf("El archivo -> %s <- NO se pudo abrir desde tiene_datos_arch().\n", nombre_arch);
                hay_Datos = 0;
        }
        else{
                printf("Archivo -> %s <- abierto desde tiene_datos_arch().\n", nombre_arch);
                // leo si hay datos
                fscanf(ptrArchivo, "%d", &lee_linea);
                // mientras no sea fin de archivo.
                while(!feof(ptrArchivo)){
                        contador++;
                        // leo si hay datos
                        fscanf(ptrArchivo, "%d", &lee_linea);
                        if(contador > 0){
                                hay_Datos = 1;
                                break;
                        }
                }
                cerrar_archivo(ptrArchivo, nombre_arch);
        }
        return hay_Datos;
}

FILE *abrir_Archivo_solo_Lectura(char *nombre_arch){
        FILE *ptrArchivo;
        ptrArchivo = fopen(nombre_arch, "r");
        if( ptrArchivo == NULL ){
                // con r Abre un archivo para lectura.
                printf("---> El archivo -> %s <- NO pudo abrirse (uso de r).\n", nombre_arch);
        }
        else{
                printf("---> Archivo -> %s <- Abierto (uso de r).\n", nombre_arch);
        }
        return ptrArchivo;
}

FILE *abrir_Archivo_lectura_escritura(char *nombre_arch){
        FILE *ptrArchivo;
        ptrArchivo = fopen(nombre_arch, "r+");
        if( ptrArchivo == NULL ){
                // con r+ Abre un archivo para actualización (lectura y escritura).
                printf("---> El archivo -> %s <- NO pudo abrirse (uso de r+).\n", nombre_arch);
        }
        else{
                printf("---> Archivo -> %s <- Abierto (uso de r+).\n", nombre_arch);
        }
        return ptrArchivo;
}

int existe_archivo(char *nombre_arch){
        FILE *ptrArchivo;
        int existe = 0;
        // Con r abre un archivo para lectura.
        ptrArchivo = fopen(nombre_arch, "r");
        if( ptrArchivo != NULL ){
                existe = 1;
                cerrar_archivo(ptrArchivo, nombre_arch);
        }
        return existe;
}

int crear_archivo(char *nombre_arch){
        int creado = 0;
        FILE *ptrArchivo;
        ptrArchivo = fopen(nombre_arch, "w");
        if( ptrArchivo == NULL ){
                // con w crea un archivo para escritura. Si el archivo ya existe, descarta el contenido actual.
                printf("----> El archivo -> %s <- no pudo crearse (abrir; uso de w).\n", nombre_arch);
        }
        else{
                creado = 1;
                printf("----> Archivo -> %s <- Creado (abierto; uso de w).\n", nombre_arch);
                cerrar_archivo(ptrArchivo, nombre_arch);
        }
        return creado;
}

void cerrar_archivo(FILE *ptrArchivo, char *nombre_arch){
        fclose(ptrArchivo);
        printf("----> Archivo -> %s <- Cerrado Correctamente.\n", nombre_arch);
}

