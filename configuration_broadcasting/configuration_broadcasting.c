#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

typedef struct {
    int iterations;
    double threshold;
} Config;

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    Config config;

    if (rank == 0) {
        // Root process initializes the configuration parameters
        config.iterations = 10;       // Example: 10 iterations
        config.threshold = 0.5;      // Example: Threshold value of 0.5
        printf("Root process initialized configuration: iterations = %d, threshold = %.2f\n",
               config.iterations, config.threshold);
    }

    // Broadcast the configuration parameters to all processes
    MPI_Bcast(&config, sizeof(Config), MPI_BYTE, 0, MPI_COMM_WORLD);

    // All processes print the received configuration
    printf("Process %d received configuration: iterations = %d, threshold = %.2f\n",
           rank, config.iterations, config.threshold);

    // Simulate an algorithm using the configuration parameters
    for (int i = 0; i < config.iterations; i++) {
        printf("Process %d: Iteration %d, checking threshold %.2f\n", rank, i + 1, config.threshold);
    }

    MPI_Finalize();
    return 0;
}
