cmake_minimum_required(VERSION 3.16.5)
project(testGL)

add_subdirectory(glfw)

add_executable(testGL main.c)
target_link_libraries(testGL PUBLIC glfw)
