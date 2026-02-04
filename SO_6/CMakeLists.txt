cmake_minimum_required(VERSION 3.10)
project(Potoki)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED on)

add_executable(potoki potoki.c)
add_executable(serv echo_serv.c)

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
