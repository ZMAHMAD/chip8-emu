cmake_minimum_required(VERSION 3.16)
project(Chip8)

find_package(SDL3 REQUIRED CONFIG)

add_executable(Chip8 main.cpp chip8.cpp)
target_link_libraries(Chip8 PRIVATE SDL3::SDL3)

add_executable(huh huh.cpp)