/*
 ============================================================================
 Name        : Project_Pthreads_Fibonacci.c
 Author      : Fernando
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* Global variables: */
int thread_count;
int *fibseq;
int n;

/* Thread function */
void *fibonacci(void *rank);

int main(int argc, char *argv[]) {

	long thread; /* Use long in case of a 64 − bit system */

	pthread_t *thread_handles;

	/* Get number of threads from command line */
	thread_count = strtol(argv[1], NULL, 10);

	thread_handles = malloc(thread_count * sizeof(pthread_t));

	printf("Ingresa el numero de fibonacci n: ");

	scanf("%d", &n);

	fibseq = (int*) malloc(n * sizeof(int));

	for (thread = 0; thread < thread_count; thread++) {

		pthread_create(&thread_handles[thread], NULL, fibonacci,
				(void*) thread);

		pthread_join(thread_handles[thread], NULL);

	}

	for (int i = 0; i < n; i++) {

		printf("%d ", fibseq[i]);

	}

	free(thread_handles);

	return 0;

}/* main */

void* fibonacci(void *rank) {

	long my_rank = (long) rank;
	/* Use long in case of 64 − bit system */

	int local_n = n / thread_count;

	int local_a = my_rank * local_n;

	int local_b = local_a + local_n - 1;

	for (int i = local_a; i <= local_b; i++) {

		if (i == 0) {
			fibseq[i] = 0;
		}

		if (i == 1) {
			fibseq[i] = 1;
		}
		if (i >= 2) {
			fibseq[i] = fibseq[i - 1] + fibseq[i - 2];
		}

	}

	return NULL;

}/* fibonacci */
