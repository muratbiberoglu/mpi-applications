#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "mpi.h"

int convert_string_to_int(char* str) {
    char *endptr;
    errno = 0; // To distinguish success/failure after call
    long val = strtol(str, &endptr, 10);

    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN)) || (errno != 0 && val == 0)) {
        perror("strtol");
        return -1;
    }

    if (endptr == str) {
        printf("No digits were found\n");
        return -1;
    }
    return (int)val;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int *array = NULL, array_size;

    if (argc < 2) {
        printf("Usage: %s <array_size>\n", argv[0]);
        return -1;
    }
    const int ARRAY_SIZE = convert_string_to_int(argv[1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 2) {
        printf("This example requires at least 2 processes.\n");
        MPI_Finalize();
        return -1;
    }

    int chunk_size = ARRAY_SIZE / size;
    int *sub_array = (int *)malloc(chunk_size * sizeof(int));

    if (rank == 0) {
        // Root process initializes the array
        array = (int *)malloc(ARRAY_SIZE * sizeof(int));
        for (int i = 0; i < ARRAY_SIZE; i++) {
            array[i] = rand() % 100; // Random integers between 0 and 99
        }
        printf("Array: ");
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", array[i]);
        }
        printf("\n");
    }

    // Scatter the array to all processes
    MPI_Scatter(array, chunk_size, MPI_INT, sub_array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Each process calculates the local sum
    int local_sum = 0;
    for (int i = 0; i < chunk_size; i++) {
        local_sum += sub_array[i];
    }

    // Reduce the local sums to the global sum on the root process
    int global_sum = 0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Root process prints the total sum
        printf("Total sum: %d\n", global_sum);
        free(array);
    }

    free(sub_array);
    MPI_Finalize();
    return 0;
}

