/* Hacer un programa en C, que:
 *  -> Reciba 2 argumentos en línea de comandos, que son nombres de archivos
 *  -> El 1er arg es una archivo de entrada y el 2do arg es el nombre de un arch de salida
 *  -> El programa va a abrir el primer archivo (no mayor a 4 o 5K) que contendrá un texto ASCII
 *  -> Leerá el archivo y ordenará las palabras alfabéticamente en una lista enlazada
 *  -> Luego pasará el comienzo de esa lista a una función, que grabará las palabras en el archvo de salida
 *  -> Con control de errores
 */

#include<stdio.h>

int main(int argc, char *argv[]){
	int i = 0;
	printf("Cantidad de Argumentos: %c", argc);

	printf("\nbin = %s", argv[0]);

	for (i = 1; i < argc; i++)
		printf("\narg%i = %s", i, argv[i]);

	printf("\n");

	return 0;
}
