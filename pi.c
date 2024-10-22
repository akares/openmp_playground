/*

Numerically compute the integral of 4/(1+x*x) from 0 to 1.

The value of this integral is Pi.

This is the serial version of the program.

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

    double x, pi, sum = 0.0;

    double start_time = omp_get_wtime();

    for (int i = 1; i <= NUM_STEPS; i++)
    {
        x = (i - 0.5) * STEP_SIZE;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = STEP_SIZE * sum;

    double run_time = omp_get_wtime() - start_time;
    printf("pi with %ld steps is %lf in %lf seconds\n", NUM_STEPS, pi, run_time);

    return 0;
}
