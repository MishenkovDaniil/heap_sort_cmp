#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct Max_heap
{
    int size = 0;
    int capacity = 0;
    unsigned long long *data = nullptr;
    unsigned long long  max = 0;
};

struct Max_heap *heap_ctor (int capacity);
void heap_insert (struct Max_heap *heap, unsigned long long val);
void heap_top (struct Max_heap *heap, unsigned long long *buffer);
void heap_remove (struct Max_heap *heap, unsigned long long *buffer);
void heapify (struct Max_heap *heap);
void heap_output (struct Max_heap *heap, int k);
void heapsort (struct Max_heap *heap);

#endif /* BINARY_HEAP_H */