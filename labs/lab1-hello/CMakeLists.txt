cmake_minimum_required(VERSION 3.27)
project(lab1_hello C)

set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)

add_executable(lab1_hello mpi_hello.c)

target_link_libraries(lab1_hello PRIVATE MPI::MPI_C)
