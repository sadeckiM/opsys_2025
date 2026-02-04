cmake_minimum_required(VERSION 3.10)
project(Procesy2)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED on)

add_executable(procesy zad3.c)

add_compile_options(
    -Wall 
    -Wextra
    -pedantic
    -Werror=return-type
    -Werror=parentheses
    -Werror=vla
    -Werror=array-bounds
    -Wcast-qual
    -Wmaybe-uninitialized
    )