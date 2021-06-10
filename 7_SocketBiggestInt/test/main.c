#include<stdio.h>
#include<string.h>
#define MAX 1000

int* GetBigInteger(char str[MAX], int arr[MAX]);
void imprimir(int size, int *p);

int main(){
	char str[MAX];
	char str2[MAX];
	int arr[MAX];
	int arr2[MAX];
	printf("Ingresa el numero A: ");
	scanf("%s", str);
	printf("Ingresa el numero B: ");
	scanf("%s", str2);
	
	int sizeA = (unsigned)strlen(str);
	int sizeB = (unsigned)strlen(str2);

	int *p, *q;
	
	p = GetBigInteger(str, arr);
	q = GetBigInteger(str2, arr2);

	imprimir(sizeA, p);
	imprimir(sizeB, q);
	
	return 0;
}

void imprimir(int size, int *p){
	printf("Tu numero es: ");
	for(int i = 0; i < size; i++){
		printf("%i", *(p + i));
	}	
	printf(" <-- int[]\n");

}

int* GetBigInteger(char str[MAX], int arr[MAX]){
	int x = (unsigned)strlen(str);
	printf("El tamaño de tu numero es de %i digitos", x);
	printf("\nTu numero es: %s <-- char[]\n\n", str);

	int i = 0;
	while(i != x){
		// Extrayendo los números del arreglo de caracteres
		// str[a] - '0'
		// = ASCII(str[a]) - ASCII('0')
		// = ASCII(str[a]) - 48
		arr[i] = str[i] - '0';
		i++;
	}

	return arr;
}
