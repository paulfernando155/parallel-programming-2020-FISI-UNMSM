/*
 ============================================================================
 Name        : Project_Mutex_Trapezoid.c
 Author      : Fernando
 Version     :
 Copyright   : Your copyright notice
 Description : Hello MPI World in C 
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

const int MAX_THREADS = 1024;

double a = 0;
double b = 20;
int n = 20;

long thread_count;
double sum;
pthread_mutex_t mutex;

void* Thread_sum(void *rank);

double Trap(double left_endpt, double right_endpt, int trap_count,
		double base_len);

double f(double x);

void Get_args(int argc, char *argv[]);

int main(int argc, char *argv[]) {

	long thread; /* Use long in case of a 64-bit system */
	pthread_t *thread_handles;

	/* Get number of threads from command line */
	Get_args(argc, argv);

	thread_handles = (pthread_t*) malloc(thread_count * sizeof(pthread_t));
	pthread_mutex_init(&mutex, NULL);
	sum = 0.0;

	/*GET_TIME(start);*/
	for (thread = 0; thread < thread_count; thread++)
		pthread_create(&thread_handles[thread], NULL, Thread_sum,
				(void*) thread);

	for (thread = 0; thread < thread_count; thread++)
		pthread_join(thread_handles[thread], NULL);

	printf("La suma es %f", sum);

	pthread_mutex_destroy(&mutex);
	free(thread_handles);
	return 0;

} /* main */

void* Thread_sum(void *rank) {

	long my_rank = (long) rank;

	double h = (b - a) / n;
	int local_n = n / thread_count;

	double local_a = a + my_rank * local_n * h;
	double local_b = local_a + local_n * h;
	double local_int = Trap(local_a, local_b, local_n, h);

	printf("%f\n", local_int);

	pthread_mutex_lock(&mutex);
	sum += local_int;
	pthread_mutex_unlock(&mutex);

	return NULL;
} /* Thread_sum */

void Get_args(int argc, char *argv[]) {

	thread_count = strtol(argv[1], NULL, 10);

}

double Trap(double left_endpt /* in */, double right_endpt /* in */,
		int trap_count /* in */, double base_len /* in */) {
	double estimate, x;
	int i;

	estimate = (f(left_endpt) + f(right_endpt)) / 2.0;
	for (i = 1; i <= trap_count - 1; i++) {
		x = left_endpt + i * base_len;
		estimate += f(x);
	}
	estimate = estimate * base_len;

	return estimate;
}

double f(double x) {
	return x * x;
}
