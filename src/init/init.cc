#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>

#include "init.hh"

void init_glfw() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Get a floating window
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
}

void init_glew() {
    if (glewInit() == GLEW_OK)
        return;

    std::cout << "Failed to initialize glew" << std::endl;
    glfwTerminate();
    exit(EXIT_FAILURE);
}

Window init_window(unsigned int width, unsigned int height, const char* title) {
    Window window(width, height, title);

    // Callback
    window.set_framebuffer_size_cb();
    window.set_mouse_cb();
    window.set_scroll_cb();

    // Mode
    window.set_input_mode(GLFW_STICKY_KEYS, GL_TRUE);
    //window.set_input_mode(GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    return window;
}
