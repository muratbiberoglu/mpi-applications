# Parallel Sum Program

This program demonstrates the use of MPI (Message Passing Interface) to compute the sum of an array in parallel. The program divides the array among multiple processes, computes partial sums locally, and then combines the results using `MPI_Reduce`.

## Problem Description

The goal is to compute the sum of an array of integers in parallel using MPI. The program follows these steps:

1. The root process (rank 0) initializes an array of random integers.
2. The array is divided evenly among all processes using `MPI_Scatter`.
3. Each process computes the sum of its portion of the array (local sum).
4. The local sums are combined into a global sum using `MPI_Reduce`.
5. The root process prints the total sum.

## Program Workflow

1. **Initialization**:
   - The root process generates an array of random integers.
   - The size of the array is provided as a command-line argument.

2. **Data Distribution**:
   - The array is divided into chunks of equal size and distributed to all processes using `MPI_Scatter`.

3. **Local Computation**:
   - Each process computes the sum of its chunk of the array.

4. **Global Reduction**:
   - The local sums are combined into a global sum using `MPI_Reduce` with the `MPI_SUM` operation.

5. **Output**:
   - The root process prints the total sum.

## Code Explanation

### Key Functions

- `convert_string_to_int(char* str)`: Converts a string to an integer with error checking.
- `MPI_Scatter`: Distributes chunks of the array to all processes.
- `MPI_Reduce`: Combines the local sums into a global sum.

### Main Function

- The root process initializes the array and distributes it using `MPI_Scatter`.
- Each process computes its local sum.
- The global sum is computed using `MPI_Reduce` and printed by the root process.

## Compilation and Execution

### Compilation

To compile the code, you can use the provided `CMakeLists.txt` file. Follow these steps:

1. Create a build directory:
    ```sh
    mkdir build
    cd build
    ```

2. Run CMake to generate the build files:
    ```sh
    cmake ..
    ```

3. Build the project:
    ```sh
    make
    ```
    This will compile the source files and produce an executable called `parallel_sum` in the build directory.

### Running the Program

To run the program, use the following command:

```sh
mpirun -np <number_of_processes> ./parallel_sum <array_size>
```

Replace `<number_of_processes>` with the number of MPI processes and `<array_size>` with the size of the array to be sorted.

## Key MPI Concepts

- `MPI_Scatter`: Used to distribute data from the root process to all processes.
- `MPI_Reduce`: Used to combine partial results (e.g., local sums) into a global result.

## Conclusion

The `parallel_sum.c` program demonstrates how to use MPI to perform parallel computations efficiently. It highlights the use of `MPI_Scatter` for data distribution and `MPI_Reduce` for result aggregation, making it a great example for learning parallel programming with MPI.
