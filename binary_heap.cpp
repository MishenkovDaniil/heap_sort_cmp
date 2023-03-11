#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "binary_heap.h"

struct Max_heap *heap_ctor (int capacity)
{
    struct Max_heap *heap = (struct Max_heap *)calloc (1, sizeof (struct Max_heap));

    heap->data = (unsigned long long *)calloc (capacity, sizeof (unsigned long long));
    heap->capacity = capacity;
    heap->size = heap->max = 0;

    return heap;
}

void heap_insert (struct Max_heap *heap, unsigned long long val)
{
    assert (heap);
    
    //if (heap->capacity == heap->size)
    // {
        // heap_realloc (heap);
    // }
    unsigned long long *heap_data = heap->data;

    heap_data[heap->size] = val;

    int idx = heap->size;

    while (idx > 0 && val > heap_data[(idx-1)/2])
    {
        heap_data[idx] = heap_data[(idx-1)/2];
        heap_data[(idx - 1)/2] = val;
        
        idx = (idx - 1)/2;
    }

    heap->size++;
}

void heap_top (struct Max_heap *heap, unsigned long long *buffer)
{   
    assert (heap && heap->data);

    if (!(heap->size))
    {
        *buffer = 0;
        return;
    }

    *buffer = heap->data[0];
}

void heap_remove (struct Max_heap *heap, unsigned long long *buffer)
{
    assert (heap && heap->data);

    if (heap->size == 0)
    {
        *buffer = 0;
        return;
    }
    
    *buffer = heap->data[0];
    heap->data[0] = heap->data[heap->size-1];
    heap->data[--(heap->size)] = 0;
    
    heapify (heap);
}

void heapify (struct Max_heap *heap)
{
    assert (heap && heap->data);
    
    int idx = 0;

    unsigned long long *heap_data = heap->data;

    while (1)
    {
        if (((2*idx +1) < heap->size && heap_data[idx] < heap_data[2*idx+1])|| ((2*idx +2)< heap->size && heap_data[idx] < heap_data[2*idx + 2]))
        {
            if ((2*idx +2)< heap->size && heap_data[2*idx+2] >= heap_data[2*idx+1])
            {
                unsigned long long temp = heap_data[2*idx+2];
                heap_data[2*idx+2] = heap_data[idx];
                heap_data[idx] = temp;
                idx = 2*idx + 2;
            }
            else 
            {
                unsigned long long temp = heap_data[2*idx+1];
                heap_data[2*idx+1] = heap_data[idx];
                heap_data[idx] = temp;
                idx = 2*idx + 1;
            }
        }
        else
        {
            break;
        }
    }
}

void heapsort (struct Max_heap *heap)
{
    assert (heap && heap->data);
    
    unsigned long long buffer[1] = {};

    while (heap->size > 1)
    {
        heap_remove (heap, buffer); 
        heap->data[heap->size] = *buffer;
    }
}