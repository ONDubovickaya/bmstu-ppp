cmake_minimum_required(VERSION 3.27)
project(lab3_collective C)

set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)

add_executable(lab3_collective mpi_collective.c)

target_link_libraries(lab3_collective PRIVATE MPI::MPI_C)
