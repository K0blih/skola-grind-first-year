cmake_minimum_required(VERSION 3.4)

# Název projektu
project(snowflakes)

# Přidání přepínačů překladače
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")

# Vytvoření programu s názvem `snowflakes`
# Vyjmenujte zde všechny zdrojové soubory, které budete používat
add_executable(snowflakes ukol10.c sdl.c dynamic_array.c)

# Přilinkování knihoven k programu (obdoba -l)
target_link_libraries(snowflakes SDL2 SDL2_image)

file(COPY snowflake.svg DESTINATION ${CMAKE_BINARY_DIR})
