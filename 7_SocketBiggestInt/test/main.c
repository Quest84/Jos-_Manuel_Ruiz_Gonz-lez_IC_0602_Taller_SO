#include<stdio.h>
#include<string.h>
#define MAX 1000

int* GetBigInteger(char str[MAX], int arr[MAX]);
void imprimir(int size, int *p);
int* suma(int *p, int *q, int *pSuma, int sizeA, int sizeB);

int main(){
	char strA[MAX];
	char strB[MAX];
	int arrA[MAX];
	int arrB[MAX];
	int arrSuma[MAX] = {0};
	printf("Ingresa el numero A: ");
	scanf("%s", strA);
	printf("Ingresa el numero B: ");
	scanf("%s", strB);
	
	int sizeA = (unsigned)strlen(strA);
	int sizeB = (unsigned)strlen(strB);

	int *p, *q;
	int *pSuma = arrSuma;

	// printf("pSuma= %d\n", *pSuma);
	
	p = GetBigInteger(strA, arrA);
	q = GetBigInteger(strB, arrB);

	printf("Tu numero es: ");
		imprimir(sizeA, p);
	printf("Tu numero es: ");
		imprimir(sizeB, q);
	
	// Error si ambos numeros tiene la misma longitud lol	
	if (sizeA <= sizeB)
		pSuma = suma(q, p, arrSuma, sizeB, sizeA);
	else
		pSuma = suma(p, q, arrSuma, sizeA, sizeB);
	
	printf("\nLa suma de tu numero es: ");
	imprimir(sizeA, pSuma);

	return 0;
}

int* suma(int *p, int *q, int arrSuma[MAX], int sizeA, int sizeB){
	// SizeA es el tamaño del numero mayor, p es el puntero al arreglo con el número más grande
	printf("\nEl número mayor es: ");
	imprimir(sizeA, p);
	printf("El número menor es: ");
	imprimir(sizeB, q);
	int temp = 0;
	int carry = 0;
	int j = sizeB - 1;
	for(int i = sizeA - 1; i >= 0; i--){
		temp = carry + (p[i] + q[j]);
		if (temp >= 10){
			carry = temp/10;
			temp = temp%10;
		} else{
			carry = 0;
		}
		j--;
		arrSuma[i] = temp;		
	}
	printf("\nUltimo carry = %d\n", carry);
	if (carry != 0)
		arrSuma[0] = arrSuma[0]+(carry*10);

	// Si la ultima operación incluye un acarreo se debe de separar ese numero
	// Ejemplo: 123 + 999 = 11 2 2
	// Una función para reordenar el arreglo?
	// arrSuma = separarArreglo(arrsuma[MAX]);
	return arrSuma; 
}


/* Estaba haciendo una multiplicación jajdaskjda 
 int* suma(int *p, int *q, int arrSuma[MAX], int sizeA, int sizeB){
	// SizeA es el tamaño del numero mayor, p es el puntero al arreglo con el número más grande
	printf("\nEl número mayor es: ");
	imprimir(sizeA, p);
	printf("El número menor es: ");
	imprimir(sizeB, q);
	int temp = 0;
	int carry = 0;
	for(int j = sizeB - 1; j >= 0; j--){
		for(int i = sizeA - 1; i >= 0; i--){
			temp = carry + (p[i] * q[j]);
			if (temp >= 10){
				carry = temp/10;
				temp = temp%10;
			} else{
				carry = 0;
			}
			arrSuma[i] = temp;		
		}
		printf("\nUltimo carry = %d\n", carry);
		if (carry != 0)
			arrSuma[0] = arrSuma[0]+(carry*10);

		// Si la ultima operación incluye un acarreo se debe de separar ese numero
		// Ejemplo: 1231321321 * 9 = 11 0 8 1 8 9 1 8 8 9
		// Una función para reordenar el arreglo?
		arrSuma = separarArreglo(arrsuma[MAX]);

		break;
	}
	return arrSuma; 
}
*/

void imprimir(int size, int *p){
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
