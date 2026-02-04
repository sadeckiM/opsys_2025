cmake_minimum_required(VERSION 3.10)
project(SHARED_MEM)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED on)

add_executable(producent producent.c)
add_executable(konsument konsument.c)
#add_executable(zad2 zad2.c)

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
