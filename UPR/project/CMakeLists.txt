cmake_minimum_required(VERSION 3.22.1)

project(project)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")  # -fsanitize=address

add_executable(project main.c dynamic_array.c alien.c player.c text.c menu.c)

find_package(SDL2 REQUIRED)

target_link_libraries(project SDL2 SDL2_image SDL2_ttf)

# normal verze

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${CMAKE_SOURCE_DIR}/assets/Arial.ttf DESTINATION ${CMAKE_BINARY_DIR}/assets)

# kelvin verze

# set(ASSETS_FILES
#     ${CMAKE_SOURCE_DIR}/bottom_alien.png
#     ${CMAKE_SOURCE_DIR}/middle_alien.png
#     ${CMAKE_SOURCE_DIR}/player_rocket.png
#     ${CMAKE_SOURCE_DIR}/player.png
#     ${CMAKE_SOURCE_DIR}/rocket.png
#     ${CMAKE_SOURCE_DIR}/space_ship.png
#     ${CMAKE_SOURCE_DIR}/top_alien.png
#     ${CMAKE_SOURCE_DIR}/Arial.ttf
# )

# foreach(FILE ${ASSETS_FILES})
#     file(COPY ${FILE} DESTINATION ${CMAKE_BINARY_DIR}/assets)
# endforeach()