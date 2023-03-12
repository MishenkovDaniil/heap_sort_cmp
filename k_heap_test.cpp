#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

#include "k_heap.h"

void k_heap_test (void);

int main ()
{
    k_heap_test ();

    return 0;
}

void k_heap_test ()
{
    size_t arr[10] = {5, 10, 25, 50, 100, 200, 300, 400, 1000};
    
    FILE *k_heap_sort = fopen ("k_heap_sort.txt", "w");
    
    for (int count = 0; count < 9; ++count)
    {
        
        fprintf (k_heap_sort, "k = %lu/n", arr[count]);

        fprintf (k_heap_sort, "[");
        
        for (int size = 100000; size <= 10000000; size += 100000)
        {
            double heapsort_time = 0;

            for (int k = 0; k < 5; ++k)
            {
                K_min_heap *heap = k_min_heap_ctor (size + 1, arr[count]);
                srand (time(NULL));
            
                clock_t t1 = 0;
                clock_t t2 = 0;

                for (int i = 0; i < size; ++i)
                {
                    unsigned int value = rand () % UINT_MAX;   
                    k_min_heap_insert (heap, value);
                }

                t1 = clock ();
                k_min_heapsort (heap);
                t2 = clock ();
                heapsort_time += (double)(1000 * (t2 - t1)) / CLOCKS_PER_SEC;
                
                k_min_heap_dtor (heap);
            }
            
            fprintf (k_heap_sort, "%d,", (int)heapsort_time/5);

            fflush (k_heap_sort);
        }

        fprintf (k_heap_sort, "]\n");
    }

    fclose (k_heap_sort); 
}
