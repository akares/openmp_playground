/*

Numerically compute the integral of 4/(1+x*x) from 0 to 1.

The value of this integral is Pi.

This is the serial version of the program.

*/

#include <stdio.h>
#include <omp.h>

const long num_steps = 100000000;

int main()
{
    int i;
    double x, pi, sum = 0.0;
    double start_time, run_time;

    double step = 1.0 / (double)num_steps;

    start_time = omp_get_wtime();

    for (i = 1; i <= num_steps; i++)
    {
        x = (i - 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    pi = step * sum;

    run_time = omp_get_wtime() - start_time;
    printf("pi with %ld steps is %lf in %lf seconds\n", num_steps, pi, run_time);

    return 0;
}
