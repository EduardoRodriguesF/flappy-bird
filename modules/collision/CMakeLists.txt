cmake_minimum_required(VERSION 3.25)

project(collision)

add_library(${PROJECT_NAME} aabb.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)
