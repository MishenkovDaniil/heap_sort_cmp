#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "k_heap.h"

K_min_heap *k_min_heap_ctor (size_t capacity, size_t k)
{
    K_min_heap *heap = (K_min_heap *)calloc (1, sizeof (K_min_heap));
    assert (heap);

    heap->data = (unsigned int *)calloc (capacity, sizeof (unsigned int));
    assert (heap->data);

    heap->capacity = capacity;
    heap->size = 0;
    heap->k = k;

    return heap;
}

void k_min_heap_insert (K_min_heap *heap, unsigned int value)
{
    assert (heap && heap->data);

    //if (heap->size == heap->capacity)
    //{
      //  k_min_heap_realloc (heap);
    //}

    heap->data[heap->size] = value;
    k_min_heap_seft_up (heap, heap->size); 
    ++heap->size;
}

void k_min_heap_seft_up (K_min_heap *heap, size_t idx)
{
    assert (heap && heap->data);
    
    while (1)
    {
        if (idx && heap->data[idx] < heap->data[(idx - 1) / heap->k])
        {
            swap_uints (heap->data + idx, heap->data + (idx - 1) / heap->k);
            idx = (idx - 1) / heap->k;
        }
        else 
        {
            return;
        }
    }
}

void k_min_heap_remove (K_min_heap *heap, unsigned int *buffer)
{
    assert (heap && heap->data);

    if (heap->size == 0)
    {
        *buffer = POISON;
        return;
    }
    
    *buffer = heap->data[0];
    heap->data[0] = heap->data[heap->size-1];
    heap->data[--(heap->size)] = 0;
    
    k_min_heapify (heap);
}

void k_min_heapify (K_min_heap *heap)
{
    assert (heap && heap->data);
    
    size_t idx = 0;
    
    while (idx * heap->k + 1 < heap->size)
    {
        size_t max_num = min (heap->size - 1, (idx + 1) * heap->k);
        
        unsigned int min = heap->data[idx * heap->k + 1];
        size_t min_idx = idx * heap->k + 1;

        for (size_t i = idx * heap->k + 2; i <= max_num; ++i)
        {
            if (heap->data[i] < min)
            {
                min = heap->data[i];
                min_idx = i;
            }
        }

        if (heap->data[idx] > min)
        {
            swap_uints (heap->data + idx, heap->data + min_idx);
            idx = min_idx;
        }
        else 
        {
            return;
        }
    }   
}

unsigned int min (unsigned int val1, unsigned int val2)
{
    return val1 < val2 ? val1 : val2;
}

void k_min_heapsort (K_min_heap *heap)
{
    assert (heap && heap->data);
    
    unsigned int buffer[1] = {};

    while (heap->size > 1)
    {
        k_min_heap_remove (heap, buffer);
        heap->data[heap->size] = *buffer;
    }
}

void swap_uints (unsigned int *val1, unsigned int *val2)
{
    unsigned int temp = *val1;
    *val1 = *val2;
    *val2 = temp;
}

void k_min_heap_dtor (K_min_heap *heap)
{
    assert (heap);

    free (heap->data);
    free (heap);
}