#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void errorCallback(int errno, const char *msg) {
    printf("GLFW error %d: %s\n", errno, msg);
}

void testSupport(int major, int minor) {
    bool support = gl3wIsSupported(major, minor);
    if (support) {
        printf("TEST OpenGL %d.%d is supported\n", major, minor);
    }
    else {
        printf("TEST OpenGL %d.%d is not supported\n", major, minor);
    }
}

int main(int argc, char **argv) {
    const int major = 3;
    const int minor = 2;

    if (glfwInit() == GLFW_FALSE) {
        puts("glfwInit returned GLFW_FALSE");
        exit(1);
    }
    glfwSetErrorCallback(errorCallback);

    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "testGL", NULL, NULL);
    if (window == NULL) {
        puts("GLFWwindow returned NULL");
        exit(1);
    }

    glfwMakeContextCurrent(window);
    if (gl3wInit() != GL3W_OK) {
        puts("gl3wInit did not return GL3W_OK");
        exit(1);
    }

    testSupport(3,2);
    testSupport(4,6);

    printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));

    float red = 0.f;
    do {
        glClearColor(red += 0.01f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
        if (red > 1.f) {
            red = 0.f;
        }
    }
    while(!glfwWindowShouldClose(window));
    glfwDestroyWindow(window);
    return 0;
}