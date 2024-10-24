cmake_minimum_required(VERSION 3.12)
project(project)

set(CMAKE_C_STANDARD 11)

add_executable(program main.c)

find_package(SDL2 REQUIRED)

target_include_directories(program PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(program SDL2 SDL2_image SDL2_ttf)