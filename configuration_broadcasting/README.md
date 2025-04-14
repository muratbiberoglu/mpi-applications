
# Configuration Broadcasting Program
This program demonstrates the use of MPI (Message Passing Interface) to broadcast configuration parameters from the root process to all other processes using `MPI_Bcast`. The program simulates a scenario where configuration parameters (e.g., number of iterations, a threshold value) are shared among all processes.

## Problem Description
The goal is to broadcast configuration parameters from the root process to all other processes using MPI. The program follows these steps:

1. The root process (rank 0) initializes a struct containing configuration parameters (e.g., `iterations` and `threshold`).
2. The configuration parameters are broadcast to all processes using `MPI_Bcast`.
3. Each process prints the received configuration parameters to confirm consistency.
4. Optionally, the program simulates an algorithm using the configuration parameters (e.g., running a dummy loop for the specified number of iterations).

## Program Workflow

1. Initialization:
    - The root process initializes a Config struct with the configuration parameters (`iterations` and `threshold`).
2. Broadcasting:
    - The `MPI_Bcast` function is used to broadcast the `Config` struct from the root process to all other processes.
3. Printing Received Configuration:
    - Each process prints the configuration parameters it received to confirm consistency.
4. Simulated Algorithm:
    - A dummy loop is run for the specified number of iterations, with optional threshold checks.

## Code Explanation

### Key Components

- `Config` Struct:
    - Contains the configuration parameters:
        - `int iterations`: Number of iterations.
        - `double threshold`: Threshold value.
- `MPI_Bcast`:
    - Used to broadcast the Config struct from the root process to all other processes.

### Main Function
- The root process initializes the Config struct with example values.
- The MPI_Bcast function broadcasts the struct to all processes.
- Each process prints the received configuration parameters.
- A dummy loop simulates an algorithm using the configuration parameters.

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
    This will compile the source files and produce an executable called `configuration_broadcasting` in the build directory.

### Running the Program

To run the program, use the following command:

```sh
mpirun -np <number_of_processes> ./configuration_broadcasting
```

Replace `<configuration_broadcasting>` with the number of MPI processes.

## Key MPI Concepts
- `MPI_Bcast`:
    - Used to broadcast data from one process (root) to all other processes.

## Conclusion
The `configuration_broadcasting.c` program demonstrates how to use `MPI_Bcast` to share configuration parameters among all processes in a parallel program. It is a simple yet effective example of broadcasting data in MPI.
