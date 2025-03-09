#include "heap.h"

Heap *heap_create(int capacity) {
    Heap *heap = (Heap *)malloc(sizeof(Heap));
    heap->arr = (HeapElement *)malloc(capacity * sizeof(HeapElement));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

void heap_insert(Heap *heap, int value, int process) {
    if (heap->size == heap->capacity) {
        return;
    }

    int i = heap->size;
    heap->arr[i].value = value;
    heap->arr[i].process = process;
    heap->size++;

    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap->arr[parent].value > heap->arr[i].value) {
            HeapElement temp = heap->arr[parent];
            heap->arr[parent] = heap->arr[i];
            heap->arr[i] = temp;
            i = parent;
        } else {
            break;
        }
    }
}

HeapElement heap_extract(Heap *heap) {
    HeapElement result = heap->arr[0];
    heap->size--;

    heap->arr[0] = heap->arr[heap->size];
    int i = 0;
    while (i < heap->size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heap->size && heap->arr[left].value < heap->arr[smallest].value) {
            smallest = left;
        }
        if (right < heap->size && heap->arr[right].value < heap->arr[smallest].value) {
            smallest = right;
        }

        if (smallest != i) {
            HeapElement temp = heap->arr[smallest];
            heap->arr[smallest] = heap->arr[i];
            heap->arr[i] = temp;
            i = smallest;
        } else {
            break;
        }
    }

    return result;
}

void heap_destroy(Heap *heap) {
    free(heap->arr);
    free(heap);
}

bool heap_is_empty(Heap *heap) {
    return heap->size == 0;
}
