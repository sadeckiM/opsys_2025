cmake_minimum_required(VERSION 3.10)
project(Potoki2)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED on)

add_executable(potoki zad5.c)
add_executable(zad6 zad6.c)
add_executable(zad7 zad7.c)

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
