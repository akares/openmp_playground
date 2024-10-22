/*

Numerically compute the integral of 4/(1+x*x) from 0 to 1.

The value of this integral is Pi.

The program was parallelized using OpenMP.
Used `parallel for` and `reduction` to parallelize the loop and aggregate
the partial results.

Extra bonus: the code structure is as close as possible to the serial version.

*/

#include <stdio.h>
#include <omp.h>

int main()
{
    printf("-----------------------------------------\n");
    printf("%s\n", __FILE__);
    printf("-----------------------------------------\n");

    const long NUM_STEPS = 100000000;
    const double STEP_SIZE = 1.0 / (double)NUM_STEPS;

    double pi, sum = 0.0;

    int num_threads;

    double start_time = omp_get_wtime();

#pragma omp parallel
    {

#pragma omp single nowait
        num_threads = omp_get_num_threads();

#pragma omp for reduction(+ : sum)
        for (int i = 1; i <= NUM_STEPS; i++)
        {
            const double x = (i - 0.5) * STEP_SIZE;
            sum += 4.0 / (1.0 + x * x);
        }
    }

    pi = STEP_SIZE * sum;

    double run_time = omp_get_wtime() - start_time;
    printf("pi with %ld steps is %lf in %lf seconds %d threads loop\n", NUM_STEPS, pi, run_time, num_threads);

    return 0;
}
