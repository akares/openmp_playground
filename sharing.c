/*

Data-sharing attribute clauses examples from OpenMP documentation.

*/

#include <stdio.h>
#include <omp.h>

// Illustrates the OpenMP default clause.
// An int is passed to a parallel region. Then:
//   -1st step : thread 0 writes "123" in the int
//   -2nd step : thread 1 prints the value of the int
// The default policy, set to shared, becomes visible when the value read by
// thread 1 is the one written by thread 0.
void default_attr()
{
    // The int that will be shared among threads
    int val = 0;

// Variables not part of a data-sharing clause will be "shared" by default.
#pragma omp parallel default(shared)
    {
        // Step 1: thread 0 writes the value
        if (omp_get_thread_num() == 0)
        {
            printf("thread 0 sets the value of \"val\" to 123\n");
            val = 123;
        }

// Threads wait each other before progressing to step 2
#pragma omp barrier

        // Step 2: thread 1 reads the value
        if (omp_get_thread_num() == 1)
        {
            printf("thread 1 reads the value of \"val\": %d\n", val);
        }
    }
}

// Illustrates the OpenMP firstprivate policy.
// This example shows that when a firstprivate variable is passed to a
// parallel region, threads work on INITIALISED copies but that whatever
// modification is made to their copies is NOT REFLECTED onto the
// original variable.
void firstprivate_attr()
{
    // Variable that will be firstprivate
    int val = 123456789;
    printf("value of \"val\" before the OpenMP parallel region: %d\n", val);
#pragma omp parallel firstprivate(val)
    {
        int thread_id = omp_get_thread_num();
        // Each thread has its own initialised copy of "val"
        printf("thread %d sees \"val\" = %d, and updates it to be %d\n", thread_id, val, thread_id);
        val = thread_id;
    }
    // Value after the parallel region; unchanged.
    printf("value of \"val\" after the OpenMP parallel region: %d\n", val);
}

// Illustrates the OpenMP lastprivate policy.
// This example shows that when a lastprivate variable is passed to a
// parallelised for loop, threads work on UNINITIALISED copies but, at the end
// of the parallelised for loop, the thread in charge of the LAST ITERATION
// sets the value of the ORIGINAL VARIABLE to that of its own copy.
void lastprivate_attr()
{
    omp_set_num_threads(4);

    // Variable that will be lastprivate
    int val = 123456789;
    printf("value of \"val\" before the OpenMP parallel region: %d\n", val);
#pragma omp parallel for lastprivate(val)
    for (int i = 0; i < omp_get_num_threads(); i++)
    {
        val = omp_get_thread_num();
    }
    // Value after the parallel region; unchanged.
    printf("value of \"val\" after the OpenMP parallel region: %d. Thread %d was therefore the last one to modify it.\n", val, val);
}

// Illustrates the OpenMP linear policy.
// @details This example shows that when a linear variable is passed to a
// parallelised for loop, the value of that variable is the ORIGINAL VALUE PLUS
// THE ITERATION LOGICAL NUMBER TIMES THE LINEAR-STEP. After the OpenMP parallel
// for, the value of the original variable is that of the linear variable at the
// LAST ITERATION.
void linear_attr()
{
    omp_set_num_threads(4);

    // Variable that will be private
    int val = 1;
    printf("value of \"val\" before the OpenMP parallel for is %d\n", val);
#pragma omp parallel for linear(val : 2)
    for (int i = 0; i < 10; i++)
    {
        printf("thread %d sees \"val\" = %d at iteration %d\n", omp_get_thread_num(), val, i);
    }
    printf("value of \"val\" after the OpenMP parallel for is %d\n", val);
}

// Illustrates the OpenMP none policy.
// This example shows that the usage of the "none" default, by comparing a
// version using implicit data-sharing clauses against that using explicit
// data-sharing clauses. Both yield the same result, but one
// REQUIRES THE EXPLICIT USAGE OF DATA-SHARING CLAUSES.
void none_attr()
{
    // Relying on the implicit default(shared)
    int implicitlyShared = 0;
#pragma omp parallel
    {
#pragma omp atomic
        implicitlyShared++;
    }
    printf("value with implicit shared: %d\n", implicitlyShared);
    // Forcing the usage of explicit data-sharing closes
    int explicitlyShared = 0;
#pragma omp parallel default(none) shared(explicitlyShared)
    {
#pragma omp atomic
        explicitlyShared++;
    }
    printf("value with explicit shared: %d\n", explicitlyShared);
}

// Illustrates the OpenMP private policy.
// This example shows that when a private variable is passed to a
// parallel region, threads work on UNINITIALISED copies and that whatever
// modification is made to their copies is NOT REFLECTED onto the original
// variable.
void private_attr()
{
    int val = 123456789;
    printf("value of \"val\" before the OpenMP parallel region: %d\n", val);
#pragma omp parallel private(val)
    {
        int thread_id = omp_get_thread_num();
        int val = val; // suppress -Wuninitialized warning because this is the point of the example
        printf("thread %d sees \"val\" = %d, and updates it to be %d\n", thread_id, val, thread_id);
        val = thread_id;
    }
    // Value after the parallel region; unchanged.
    printf("value of \"val\" after the OpenMP parallel region: %d\n", val);
}

// Illustrates the OpenMP shared policy.
// This example shows that a variable passed as shared to a parallel region
// is SHARED ACROSS ALL THREADS of that region. It becomes visible by letting
// a thread modify its value, and another thread prints its value afterwards.
// The whole process is made more visible by also printing the value of the
// original variable before and after the OpenMP parallel region.
void shared_attr()
{
    // The int that will be shared among threads
    int val = 0;
    printf("value of \"val\" before the OpenMP parallel region: %d\n", val);
#pragma omp parallel shared(val)
    {
        // Step 1: thread 0 writes the value
        if (omp_get_thread_num() == 0)
        {
            printf("thread 0 sets the value of \"val\" to 123\n");
            val = 123;
        }
// Threads wait each other before progressing to step 2
#pragma omp barrier
        // Step 2: thread 1 reads the value
        if (omp_get_thread_num() == 1)
        {
            printf("thread 1 reads the value of \"val\": %d\n", val);
        }
    }
    printf("value of \"val\" after the OpenMP parallel region: %d\n", val);
}

int main()
{
    printf("-----------------------------------------\n");
    printf("%s\n", __FILE__);
    printf("-----------------------------------------\n");

    omp_set_num_threads(2);

    printf("[default]:\n");
    default_attr();

    printf("[firstprivate]:\n");
    firstprivate_attr();

    printf("[lastprivate]:\n");
    lastprivate_attr();

    printf("[linear]:\n");
    linear_attr();

    printf("[none]:\n");
    none_attr();

    printf("[private]:\n");
    private_attr();

    printf("[shared]:\n");
    shared_attr();
}
