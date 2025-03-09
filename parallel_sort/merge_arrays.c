#include "merge_arrays.h"

int* merge_arrays(int count, int array_count, int* sizes, int** values) {
    Heap *heap = heap_create(array_count);

    int *result = (int *)malloc(count * sizeof(int));
    int result_size = 0;

    // array of pointers that point to next element to be pushed to heap
    int* indexes = (int *)malloc(array_count * sizeof(int));
    for (int i = 0; i < array_count; i++) {
        indexes[i] = 0;
    }

    for (int i = 0; i < array_count; i++) {
        int* index = &indexes[i];
        if (*index >= sizes[i])
            continue;
        heap_insert(heap, values[i][*index], i);
        *index = *index + 1;
    }

    while (!heap_is_empty(heap)) {
        HeapElement element = heap_extract(heap);
        result[result_size++] = element.value;

        int process = element.process;
        int index = indexes[process];
        int size = sizes[process];
        if (index < size) {
            heap_insert(heap, values[process][index], process);
            indexes[process] = index + 1;
        }
    }

    free(indexes);
    heap_destroy(heap);

    return result;
}
