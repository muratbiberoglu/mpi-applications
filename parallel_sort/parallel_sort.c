#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include "mpi.h"
#include "merge_arrays.h"

void random_array(int** array, int* size, int given_size) {
    *array = (int *)malloc(given_size * sizeof(int));
    *size = given_size;
    for (int i = 0; i < *size; i++) {
        (*array)[i] = rand();
    }
}

void write_array_to_file(int* array, int size, char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    for (int i = 0; i < size; i++) {
        if (i) fprintf(file, ",");
        fprintf(file, "%d", array[i]);
    }
    fprintf(file, "\n");
    fclose(file);
}

int compare(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int convert_string_to_int(char* str) {
    char *endptr;
    errno = 0; // To distinguish success/failure after call
    long val = strtol(str, &endptr, 10);

    // Check for various possible errors
    if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
        || (errno != 0 && val == 0)) {
        perror("strtol");
        return -1;
    }

    if (endptr == str) {
        printf("No digits were found\n");
        return -1;
    }
    return val;
}

int main(int argc, char *argv[]) {
    int rank, size;
    int *array, array_size;
    if (argc < 2) {
        printf("Usage: %s <array_size>\n", argv[0]);
        return -1;
    }
    const int ARRAY_SIZE = convert_string_to_int(argv[1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size < 3) {
        printf("This example requires at least 3 processes.\n");
        MPI_Finalize();
        return -1;
    }

    if (rank == 0) {
        // Generate & print array
        random_array(&array, &array_size, ARRAY_SIZE);
        char* random_array_filename = "random_array.txt";
        write_array_to_file(array, array_size, random_array_filename);
        printf("Written random array of size %d to %s\n", array_size, random_array_filename);

        // Divide array into equal blocks and send to other processes
        int block_size = array_size / (size - 1);
        int block_start = 0;
        for (int p = 1; p < size; p++) {
            int send_size = p == size - 1 ? array_size - block_start : block_size;
            MPI_Send(&send_size, 1, MPI_INT, p, 0, MPI_COMM_WORLD);
            MPI_Send(array + block_start, send_size, MPI_INT, p, 0, MPI_COMM_WORLD);
            printf("Process %d sent array segment to process %d. Size: %d\n", rank, p, send_size);
            block_start += block_size;
        }

        // Receive sorted arrays from other processes
        int array_count = size - 1;
        int* sizes = (int *)malloc(array_count * sizeof(int));
        int** values = (int **)malloc(array_count * sizeof(int *));
        int received_size = 0;
        for (int p = 1; p < size; p++) {
            MPI_Recv(&received_size, 1, MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            int* received_array = (int *)malloc(received_size * sizeof(int));
            values[p - 1] = received_array;
            sizes[p - 1] = received_size;
            MPI_Recv(received_array, received_size, MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Process %d received sorted array segment from process %d. Size: %d\n", rank, p, received_size);
        }

        // Merge sorted arrays
        int* sorted_array = merge_arrays(array_size, array_count, sizes, values);
        char* sorted_array_filename = "sorted_array.txt";
        write_array_to_file(sorted_array, array_size, sorted_array_filename);
        printf("Written sorted array of size %d to %s\n", array_size, sorted_array_filename);

        // Free memory
        for (int p = 1; p < size; p++) {
            free(values[p - 1]);
        }
        free(sizes);
        free(values);
        free(sorted_array);
    } else {
        // Receive array from process 0
        MPI_Recv(&array_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        array = (int *)malloc(array_size * sizeof(int));
        MPI_Recv(array, array_size, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Process %d received array segment. Size = %d\n", rank, array_size);

        // Sort array
        qsort(array, array_size, sizeof(int), compare);
        printf("Process %d sorted array segment. Size: %d\n", rank, array_size);

        // Send sorted array to process 0
        MPI_Send(&array_size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(array, array_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
        printf("Process %d sent sorted array segment to process %d. Size: %d\n", rank, 0, array_size);
    }

    // Free memory
    free(array);

    MPI_Finalize();
    return 0;
}
