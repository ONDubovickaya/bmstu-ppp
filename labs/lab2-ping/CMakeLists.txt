cmake_minimum_required(VERSION 3.27)
project(lab2_ping C)

set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)

add_executable(lab2_ping mpi_ping.c)

target_link_libraries(lab2_ping PRIVATE MPI::MPI_C)
