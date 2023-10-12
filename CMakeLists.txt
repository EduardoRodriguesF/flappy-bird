cmake_minimum_required(VERSION 3.20)

project(flappy_bird)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(${PROJECT_NAME} "src/main.cpp" "src/game.cpp" "src/entities.cpp")

include_directories(modules)
add_subdirectory(modules/clock)
add_subdirectory(modules/collision)
add_subdirectory(modules/resource)
add_subdirectory(modules/savefile)
add_subdirectory(modules/split)

target_link_libraries(${PROJECT_NAME} SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer clock collision resource savefile)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
