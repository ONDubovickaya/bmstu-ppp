cmake_minimum_required(VERSION 3.27)
project(lab2_ping_wait C)

set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)

add_executable(lab2_ping_wait mpi_ping_wait.c)

target_link_libraries(lab2_ping_wait PRIVATE MPI::MPI_C)
