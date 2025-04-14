cmake_minimum_required(VERSION 3.10)
project(ParallelSum C)

set(CMAKE_C_STANDARD 99)

# Find MPI package
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

# Add the executable
add_executable(parallel_sum parallel_sum.c)

# Use mpicc for parallel_sort.c
set_source_files_properties(parallel_sum.c PROPERTIES COMPILE_FLAGS "${MPI_C_COMPILE_FLAGS}")

# Link MPI libraries
target_link_libraries(parallel_sum ${MPI_C_LIBRARIES})
