#ifndef K_HEAP_H
#define K_HEAP_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

static const unsigned int POISON = 0xDEADBEEF;

struct K_min_heap
{
    unsigned int *data = nullptr;
    size_t size = 0;
    size_t capacity = 0;
    size_t k = 0;
};

K_min_heap *k_min_heap_ctor (size_t capacity, size_t k);
void k_min_heap_insert (K_min_heap *heap, unsigned int value);
void k_min_heap_seft_up (K_min_heap *heap, size_t idx);
void k_min_heap_remove (K_min_heap *heap, unsigned int *buffer);
void k_min_heapify (K_min_heap *heap);
unsigned int min (unsigned int val1, unsigned int val2);
void k_min_heapsort (K_min_heap *heap);
void swap_uints (unsigned int *val1, unsigned int *val2);
void k_min_heap_dtor (K_min_heap *heap);

#endif /* K_HEAP_H */