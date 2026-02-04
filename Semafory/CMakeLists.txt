cmake_minimum_required(VERSION 3.10)
project(Semafory)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED on)

add_executable(zad1 zad1.c)
add_executable(producent producent.c)
target_include_directories(producent PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

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
    -lrt
    -pthread
    )
