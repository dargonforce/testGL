#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#define DEFAULT_MAJOR (3)
#define DEFAULT_MINOR (3)

void errorCallback(int err, const char *msg) {
    printf("GLFW error %d: %s\n", err, msg);
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

bool parseString(const char *string, int *rv) {
    *rv = strtoimax(string, NULL, 10);
    if (*rv == UINTMAX_MAX && errno == ERANGE) {
        printf("Unable to parse \"%s\"\n", string);
        return false;
    }
    else {
        return true;
    }
}

int main(int argc, char **argv) {
    int major, minor;
    switch (argc) {
        case 1:
        {
            // use defaults
            major = DEFAULT_MAJOR;
            minor = DEFAULT_MINOR;
        }
        break;
        case 3:
        {
            bool success = true;
            const char *majorString = argv[1];
            const char *minorString = argv[2];
            success = parseString(argv[1], &major);
            success = parseString(argv[2], &minor) && success;
            if (!success) {
                exit(1);
            }
        }
        break;
        default:
        {
            printf("Expected 2 or 0 arguments, got %d\n", argc);
            exit(1);
        }
        break;
    }

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

    testSupport(major, minor);

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
