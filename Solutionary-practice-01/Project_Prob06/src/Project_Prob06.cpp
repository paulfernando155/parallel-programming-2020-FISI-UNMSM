/*
 ============================================================================
 Name        : Project_Prob06.c
 Author      : Fernando
 Version     :
 Copyright   : Your copyright notice
 Description : Compute Pi in MPI C++
 ============================================================================
 */
#include <math.h> 
#include "mpi.h" 
#include <iostream>
using namespace std;

void Get_input(int my_rank, int comm_sz, int* n, int* x);

int main(void) {

	int my_rank, comm_sz, n, local_n, x;
	int *A, *A_local;

	int local_int, total_int;

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

	srand(time(NULL) + my_rank);

	Get_input(my_rank, comm_sz, &n, &x);

	local_n = n / comm_sz;

	A = new int[n];

	A_local = new int[local_n];

	if (my_rank == 0) {

		for (int i = 0; i < n; i++) {

			A[i] = rand() % 100 + 1;

		}

	}

	MPI_Scatter(A, local_n, MPI_INT, A_local, local_n, MPI_INT, 0,
	MPI_COMM_WORLD);

	local_int = 0;

	for (int i = 0; i < local_n; i++) {
		if (x == A_local[i]) {
			local_int++;
		}
	}

	MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0,
	MPI_COMM_WORLD);

	if (my_rank == 0) {
		printf("El numero de veces que aparece el elemento %d es %d\n", x,
				total_int);
	}

	MPI_Finalize();

	return 0;
}

void Get_input(int my_rank, int comm_sz, int* n, int *x) {

	if (my_rank == 0) {

		printf(
				"Ingrese el tamaño del vector y la variable que debe coincidir \n");
		scanf("%d %d", n, x);

	}

	MPI_Bcast(n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(x, 1, MPI_INT, 0, MPI_COMM_WORLD);
}
