cmake_minimum_required(VERSION 3.10)
project(ConfigurationBroadcasting C)

set(CMAKE_C_STANDARD 99)

# Find MPI package
find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

# Add the executable
add_executable(configuration_broadcasting configuration_broadcasting.c)

# Use mpicc for parallel_sort.c
set_source_files_properties(configuration_broadcasting.c PROPERTIES COMPILE_FLAGS "${MPI_C_COMPILE_FLAGS}")

# Link MPI libraries
target_link_libraries(configuration_broadcasting ${MPI_C_LIBRARIES})
