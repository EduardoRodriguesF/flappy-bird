cmake_minimum_required(VERSION 3.25)

project(resource)

add_library(${PROJECT_NAME} texture.cpp sound.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer)
