/*

Numerically compute the integral of 4/(1+x*x) from 0 to 1.

The value of this integral is Pi.

The program was parallelized using OpenMP.
Used the parallel pragma to fork a team of threads to compute the integral.

*/

#include <stdio.h>
#include <omp.h>

double calc_pi_chunk(int chunk_num, long num_chunks, long num_steps, double step_size)
{
    double partial_sum = 0.0;
    double x = 0.0;

    // The approach is called "Cyclic distribution of the loop iterations".
    //
    // The first thread will calculate the sum for the 1st, num_chunks+1st, num_chunks*2+1st, etc. steps.
    // The second thread will calculate the sum for the 2nd, num_chunks+2nd, num_chunks*2+2nd, etc. steps.
    // And so on.
    //
    // The chunk_num is simply the thread number and num_chunks is the total number of threads.

    for (int i = chunk_num; i <= num_steps; i += num_chunks)
    {
        x = (i - 0.5) * step_size;
        partial_sum += 4.0 / (1.0 + x * x);
    }

    return step_size * partial_sum;
}

int main()
{
    printf("-----------------------------------------\n");
    printf("%s\n", __FILE__);
    printf("-----------------------------------------\n");

    const int MAX_THREADS = 8;
    const long NUM_STEPS = 100000000;
    const double STEP_SIZE = 1.0 / (double)NUM_STEPS;

    for (int num_threads = 1; num_threads <= MAX_THREADS; num_threads++)
    {
        omp_set_num_threads(num_threads);

        double pi = 0.0;
        double start_time = omp_get_wtime();

#pragma omp parallel
        {
            const int chunk_num = omp_get_thread_num();
            const int num_chunks = omp_get_num_threads();

#pragma omp single
            printf("Running on %d threads\n", num_threads);

            double pi_chunk = calc_pi_chunk(chunk_num, num_chunks, NUM_STEPS, STEP_SIZE);

#pragma omp atomic
            pi += pi_chunk;
        }

        double run_time = omp_get_wtime() - start_time;
        printf("pi with %ld steps is %lf in %lf seconds %d threads\n", NUM_STEPS, pi, run_time, num_threads);
    }

    return 0;
}
