#include <stdio.h>
#include <omp.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[]) {
	double x, final;
	int i, nthreads;
	long long N = 1000000000;

	final = 1.0;
	x = 1 + 1.0 / N;

	clock_t start = omp_get_wtime();
	omp_set_num_threads(16);

#pragma omp parallel default(none) private(i) shared(x, nthreads, N) reduction(*:final)
	{
#pragma omp for
		for (i = 0; i < N; i++) {
			final *= pow(x, sin(i) * cos(i));
		}

#pragma omp single
		{
			nthreads = omp_get_num_threads();
			printf("There are %d threads\n", nthreads);
		}
	}

	clock_t end = omp_get_wtime();
	double time_spent = (end - start);

	printf("Execution time (parallel): %f\n", time_spent);
	printf("Final result = %lf\n", final);

	return 0;
}
