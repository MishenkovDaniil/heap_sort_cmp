#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <stdlib.h>

#include "binary_heap.h"

void binary_heap_test (void);

int main ()
{
    binary_heap_test ();

    return 0;
}
void binary_heap_test ()
{
    FILE *binary_heap_sort = fopen ("binary_heap_sort.txt", "w");
    fprintf (binary_heap_sort, "[");
    
    for (int size = 100000; size <= 10000000; size += 100000)
    {
        double heapsort_time = 0;

        for (int k = 0; k < 5; ++k)
        {
            Max_heap *heap = heap_ctor (size + 1);
            srand (time(NULL));
        
            clock_t t1 = 0;
            clock_t t2 = 0;


            for (int i = 0; i < size; ++i)
            {
                unsigned int value = rand () % UINT_MAX;   
                heap_insert (heap, value);
            }

            t1 = clock ();
            heapsort (heap);
            t2 = clock ();
            heapsort_time += (double)(1000 * (t2 - t1)) / CLOCKS_PER_SEC;
            
            free (heap->data);
            free (heap);
        }
        
        fprintf (binary_heap_sort, "%d,", (int)heapsort_time/5);

        fflush (binary_heap_sort);
    }

    fprintf (binary_heap_sort, "]\n");

    fclose (binary_heap_sort); 
}
