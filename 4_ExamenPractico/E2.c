#include<stdio.h>

int main(){
	// Crear un array de tipo caracter de tamaño 5 y de nombre arrayChar
	char arrayChar[5];
	int i = 0;

	// Iniciarlizarlo de a-e
	for(int car = 97; car < 102; car++){
		arrayChar[i] = car;
		i++;
	}
	
	// Crear un puntero hacia un char de nombre punteroChar e inicializarlo con arrayChar
	char *punteroChar = arrayChar;

	//Crear un puntero hacia un char de nombre punteroCharDos e inicializarlo con la direccion del primer elemento (index) del array "arrayChar"
	
	char *punteroDosChar = &arrayChar[1];

	// Imprimir el contenido del primer elemento del array "arrayChar"
	printf("\nContenido [0] de arrayChar = %c", arrayChar[0]);


	// Imprimir el contenido del primer elemento del putnero punteroChar
	printf("\nContenido del [0] de punteroChar = %c", );

	// Imprimir el contenido del primer elemento del puntero punteroCharDos
	printf("\nContenido del [0] de punteroCharDos = %c", );

	// Imprimir el contenido del quinto elemento del array "arrayChar"
	printf("\nContenido dl [5] de arrayChar = %c", arrayChar[4]);

	//Imprimir el contendo del quinto elemento del puntero "punteroChar" con aritmetica de punteros
	printf("\nContenido del [5] de punteroChar con aritmetica de punteros = %c", );

	// Imprimir el contenido del quinto elemento del puntero "punteroCharDos" con aritmética de punteros
	printf("\nContenido del [5] de punteroCharDos con arimética de punteros = %", );

	// Usar una estructura repetitiva para imprimir el contenido de todos los elementos de "punteroCharDos"
	for (int i = 0; )

	return 0;
}
