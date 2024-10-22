/*

This program is a simple example of how to properly force OpenMP to create
exactly one thread per core.

This (may) be useful if you want to fully utilize the available cores but
avoid oversubscription.

*/

#include "omp.h"
#include <stdio.h>

int main()
{
    printf("-----------------------------------------\n");
    printf("%s\n", __FILE__);
    printf("-----------------------------------------\n");

    const int num_cores = omp_get_num_procs();
    printf("Number of cores: %d\n", num_cores);

    // IMPORTANT: Explicitly disable dynamic thread management.
    omp_set_dynamic(0);

    // Then ask for the fixed number of threads.
    omp_set_num_threads(num_cores);

    int num_threads;

#pragma omp parallel
    {
#pragma omp single
        {
            // Then check the allocated number of threads.
            // IMPORTANT: Only can quiery the effective number of threads inside
            // the parallel region.
            num_threads = omp_get_num_threads();
            printf("Number of threads: %d\n", num_threads);
        }

        // Do some work here.
        const int thread_id = omp_get_thread_num();
        printf("Thread %d of %d\n", thread_id, num_threads);
    }

    return 0;
}
