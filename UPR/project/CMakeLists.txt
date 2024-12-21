cmake_minimum_required(VERSION 3.4)

project(project)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")  # -fsanitize=address

add_executable(project main.c dynamic_array.c alien.c player.c text.c)

find_package(SDL2 REQUIRED)

target_link_libraries(project SDL2 SDL2_image)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
