#include <iostream>
#include <stdio.h>
#include <thread>
#include <cstdlib>
#include <ctime>
using namespace std;

#define NUM_THREADS 2
#define FILA_A 1
#define CA_FB 2
#define COLUMNA_B 1

int A[FILA_A][CA_FB]; //Iniciar tamaño de matriz A
int B[CA_FB][COLUMNA_B]; //Iniciar tamaño de matriz B
int C[FILA_A][COLUMNA_B]; //Iniciar tamaño de matriz C

//Funcion de multiplicacion
void multiplicacion(void *arg){
	for (int i = 0; i < FILA_A; ++i){
		for (int j = 0; j < COLUMNA_B; ++j){
			C[i][j] = 0;
			for (int k = 0; k < CA_FB; ++k){
				C[i][j] += A[i][k]*B[k][j]; 
			}
		}
	}
}

int main(int argc, char *argv[]) {
    cout << "===========================================================" << endl;
    cout << "\tThreads" << endl;
    cout << "===========================================================" << endl << endl;

    //Generar numeros random por cada ejecucion del programa
    srand(time(0));

    //Generar numeros para matriz A
    for (int i = 0; i < FILA_A; i++){
    	for (int j = 0; j < CA_FB; j++){
    		A[i][j] = rand() % 5;
    	}
    }

    //Generar numeros para matriz B
    for (int i = 0; i < CA_FB; i++){
    	for (int j = 0; j < COLUMNA_B; j++){
    		B[i][j] = rand() % 5;
    	}
    }

    //Imprimir matriz A
    cout<<"Matriz A"<<endl;
    for (int i = 0; i < FILA_A; i++){
    	for (int j = 0; j < CA_FB; j++){
    		cout<<A[i][j]<<" ";
    	}
    	cout<<endl;
    }

    //Imprimir matriz B
    cout<<endl<<"Matriz B"<<endl;
    for (int i = 0; i < CA_FB; i++){
    	for (int j = 0; j < COLUMNA_B; j++){
    		cout<<B[i][j]<<" ";
    	}
    	cout<<endl;
    }

    //Generar numero de threads
    thread threads[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
    	int *p;
        threads[i] = thread(multiplicacion,(void*)(p));
    }

    // We have to wait for the threads, otherwise the main thread may finish first
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    //Imprimir matriz C
    cout<<endl<<"Matriz C"<<endl;
    for (int i = 0; i < FILA_A; i++){
    	for (int j = 0; j < COLUMNA_B; j++){
    		cout<<C[i][j]<<" ";
    	}
    	cout<<endl;
    }

    return EXIT_SUCCESS;
}