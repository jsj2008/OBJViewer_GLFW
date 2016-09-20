
#pragma once

#include <iostream>
#include <libs/lib/glew.h>
#include <libs/lib/glfw3.h>

static int init_GLFW(GLFWwindow **window, int width, int height, bool fullscreen) {
    std::cout << "Abriendo Motor Grafico" << std::endl;
    if (!glfwInit())
        return 1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWmonitor *monitor = NULL;
    if (fullscreen) {
        monitor = glfwGetPrimaryMonitor();
        width = glfwGetVideoMode(monitor)->width;
        height = glfwGetVideoMode(monitor)->height;
    }
    *window = glfwCreateWindow(width, height, "Sivax Extreme Engine", monitor, NULL);
    if (!*window) {
        glfwTerminate();
        return 2;
    }
    glfwMakeContextCurrent(*window);
    glfwGetFramebufferSize(*window, &width, &height);
    glViewport(0, 0, width, height);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK) {
        std::cout << "glewInit failed, aborting." << std::endl;
    }
    //glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glPointSize(50.0f);
    glEnable(GL_CULL_FACE);
    glClearColor(0.25f, 0.25f, 0.35f, 0.0f);

    return 0;
}

