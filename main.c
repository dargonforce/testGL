#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

void errorCallback(int errno, const char *msg) {
    printf("GLFW error %d: %s\n", errno, msg);
}

int main(int argc, char **argv) {
    if (glfwInit() == GLFW_FALSE) {
        puts("glfwInit returned GLFW_FALSE");
        exit(1);
    }
    glfwSetErrorCallback(errorCallback);

    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    GLFWwindow *window = glfwCreateWindow(800, 600, "testGL", NULL, NULL);
    if (window == NULL) {
        puts("GLFWwindow returned NULL");
        exit(1);
    }
    do {

        glfwPollEvents();
    }
    while(!glfwWindowShouldClose(window));

    glfwDestroyWindow(window);
    return 0;
}