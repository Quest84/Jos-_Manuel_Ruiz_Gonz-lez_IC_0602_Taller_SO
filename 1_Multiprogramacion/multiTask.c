#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void task1(){
	printf("Task 1\n");
}

void task2(){
	printf("Task 2\n");
}

void task3(){
	printf("Task 3\n");
}

void main () {
	time_t t1;
	double tInicial = time(&t1);
	printf("Presiona Ctrl+C para finalizar el bucle");
	getchar();
	while(1){
	   	time_t t2;
	   
		double tFinal = time(&t1);// - time(&t1);
		int tTranscurrido = tFinal - tInicial;
	
		if ((tTranscurrido % 2)==0)
			task1();
		if ((tTranscurrido % 3)==0)
			task2();
		if ((tTranscurrido % 4)==0)
			task3(); 
		//printf("T = %i\n", tTranscurrido);
	}
}
