#include <stdio.h>
#include <omp.h>

double calc_pi_chunk(int chunk_num, long num_chunks, long num_steps, double step)
{
    double sum = 0.0;
    double x = 0.0;

    for (int i = chunk_num; i <= num_steps; i += num_chunks)
    {
        x = (i - 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }

    return step * sum;
}

int main()
{
    const int MAX_THREADS = 8;
    const long NUM_STEPS = 100000000;

    double step = 1.0 / (double)NUM_STEPS;

    for (int num_threads = 1; num_threads <= MAX_THREADS; num_threads++)
    {
        omp_set_num_threads(num_threads);

        double pi = 0.0;
        double start_time = omp_get_wtime();

#pragma omp parallel
        {
            const int chunk_num = omp_get_thread_num();
            const int num_chunks = omp_get_num_threads();
            pi += calc_pi_chunk(chunk_num, num_chunks, NUM_STEPS, step);
        }

        double run_time = omp_get_wtime() - start_time;
        printf("pi with %ld steps is %lf in %lf seconds %d threads\n", NUM_STEPS, pi, run_time, num_threads);
    }

    return 0;
}
