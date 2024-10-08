cmake_minimum_required(VERSION 3.27)
project(lab4_matrix C)

set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)

add_executable(lab4_matrix mpi_matrix.c)

target_link_libraries(lab4_matrix PRIVATE MPI::MPI_C)
