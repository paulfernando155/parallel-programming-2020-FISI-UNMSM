/*
 ============================================================================
 Name        : Project_Factorial.c
 Author      : Fernando
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
int n;
int result = 1;

void* factorial(void *rank);

int main(int argc, char *argv[]) {

	long thread; /* Use long in case of a 64 − bit system */

	pthread_t *thread_handles;

	/* Get number of threads from command line */
	thread_count = strtol(argv[1], NULL, 10);

	thread_handles = malloc(thread_count * sizeof(pthread_t));

	printf("Ingresa el numero que desea hallar su factorial: ");

	scanf("%d", &n);

	for (thread = 0; thread < thread_count; thread++) {

		pthread_create(&thread_handles[thread], NULL, factorial,
				(void*) thread);

	}

	for (thread = 0; thread < thread_count; thread++) {

		pthread_join(thread_handles[thread], NULL);

	}

	printf("EL factorial de %d es : %d\n", n, result);

	free(thread_handles);

	return 0;

}/* main */

void* factorial(void *rank) {

	long my_rank = (long) rank;
	/* Use long in case of 64 − bit system */

	int local_n = n / thread_count;

	int local_a = my_rank * local_n;

	int local_b = local_a + local_n - 1;

	for (int i = local_a; i <= local_b; i++) {

		if (i > 0) {
			result *= i;
		}

		printf("%d", i);

	}

	return NULL;

}/* fibonacci */
