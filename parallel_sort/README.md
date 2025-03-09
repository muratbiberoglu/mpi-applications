# Parallel Sort

This project implements a parallel sorting algorithm using MPI (Message Passing Interface). The project consists of several C source files and headers that work together to perform the sorting operation. Below is a summary of each file and its functionality.

## Files

### 1. `parallel_sort.c`

This is the main file that orchestrates the parallel sorting process using MPI.

- **Functions:**
  - `random_array(int** array, int* size, int given_size)`: Generates a random array of integers.
  - `write_array_to_file(int* array, int size, char* filename)`: Writes an array of integers to a file.
  - `compare(const void *a, const void *b)`: Comparison function used by `qsort`.
  - `convert_string_to_int(char* str)`: Converts a string to an integer, with error checking.
  - `main(int argc, char *argv[])`: The main function that initializes MPI, generates the random array, distributes it among processes, gathers the sorted subarrays, and writes the final sorted array to a file.

### 2. `merge_arrays.c`

This file contains the implementation of the function that merges multiple sorted arrays into a single sorted array.

- **Functions:**
  - `merge_arrays(int count, int array_count, int* sizes, int** values)`: Merges multiple sorted arrays into a single sorted array using a min-heap.

### 3. `heap.c`

This file contains the implementation of a min-heap, which is used in the merging process.

- **Functions:**
  - `heap_create(int capacity)`: Creates a new heap with the given capacity.
  - `heap_destroy(Heap *heap)`: Frees the memory allocated for the heap.
  - `heap_insert(Heap *heap, int value, int process)`: Inserts a new element into the heap.
  - `heap_extract(Heap *heap)`: Extracts the minimum element from the heap.
  - `heap_is_empty(Heap *heap)`: Checks if the heap is empty.

### 4. `heap.h`

This header file contains the declarations for the heap functions and the definitions of the `Heap` and `HeapElement` structures.

### 5. `merge_arrays.h`

This header file contains the declaration for the `merge_arrays` function.

### 6. `check_sorted.py`

This Python script reads arrays from files and checks whether the array in `sorted_array.txt` is sorted correctly and whether it is equal to the sorted version of the array in `random_array.txt`.

- **Functions:**
  - `read_array_from_file(filename)`: Reads an array from a file.
  - `is_sorted(array)`: Checks if an array is sorted.
  - `main()`: Main function that reads the arrays, checks if they are sorted, and verifies their correctness.

## Usage

### Compiling the Code

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
    This will compile the source files and produce an executable called `parallel_sort` in the build directory.

### Running the Program

To run the program, use the following command:

```sh
mpirun -np <number_of_processes> ./parallel_sort <array_size>
```

Replace `<number_of_processes>` with the number of MPI processes and `<array_size>` with the size of the array to be sorted.

### Verifying the Sorted Array

To verify that the sorted array is correct, run the `check_sorted.py` script:

```sh
python check_sorted.py
```

This script will read the arrays from `sorted_array.txt` and `random_array.txt`, check if the array in `sorted_array.txt` is sorted correctly, and verify that it is equal to the sorted version of the array in `random_array.txt`.
