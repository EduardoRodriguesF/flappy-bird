cmake_minimum_required(VERSION 3.25)

project(clock)

add_library(${PROJECT_NAME} clock.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
