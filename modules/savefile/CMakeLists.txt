cmake_minimum_required(VERSION 3.25)

project(savefile)

add_library(${PROJECT_NAME} encryption.cpp savefile.cpp)
target_link_libraries(${PROJECT_NAME} SDL2::SDL2 split)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)
