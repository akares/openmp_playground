#include <omp.h>
#include <stdio.h>

int main()
{
    printf("-----------------------------------------\n");
    printf("%s\n", __FILE__);
    printf("-----------------------------------------\n");

#pragma omp parallel
    {
        int id = omp_get_thread_num();
        printf("Hello(%d), ", id);
        printf("World(%d)\n", id);
    }
    return 0;
}
