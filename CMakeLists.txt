cmake_minimum_required(VERSION 3.20)

project(flappy_bird)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} "src/main.cpp" "src/game.cpp")

target_link_libraries(${PROJECT_NAME} SDL2::SDL2)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
