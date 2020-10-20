cmake_minimum_required(VERSION 3.16)
project(testGL)

set(OpenGL_GL_PREFERENCE GLVND)

add_subdirectory(gl3w)

add_subdirectory(glfw)

find_package(OpenGL REQUIRED)

add_executable(testGL main.c)
target_link_libraries(testGL PUBLIC glfw OpenGL::OpenGL gl3w)
