cmake_minimum_required(VERSION 3.27)
project(lab2_ping_deadlock C)

set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)

add_executable(lab2_ping_deadlock mpi_ping_deadlock.c)

target_link_libraries(lab2_ping_deadlock PRIVATE MPI::MPI_C)
