#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int value;
    int process;
} HeapElement;

typedef struct {
    HeapElement *arr;
    int capacity;
    int size;
} Heap;

Heap *heap_create(int capacity);

void heap_destroy(Heap *heap);

void heap_insert(Heap *heap, int value, int process);

HeapElement heap_extract(Heap *heap);

bool heap_is_empty(Heap *heap);


#endif // HEAP_H
