#include <iostream>
#include <cstdlib>

#include "window.hh"

Window::Window(unsigned int w, unsigned int h, const char* title)
    : width(w), height(h)
{
    this->window = glfwCreateWindow(width, height, title, NULL, NULL);

    if (this->window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(this->window);
}

bool Window::should_close() const {
    return glfwWindowShouldClose(this->window);
}

bool Window::key_press(int key) const {
    return glfwGetKey(this->window, key) == GLFW_PRESS;
}

void Window::swap_buffers() {
    glfwSwapBuffers(this->window);
}

float Window::get_ratio() const {
    return (float) width / (float) height;
}

void Window::set_input_mode(int mode, int value) {
    glfwSetInputMode(this->window, mode, value);
}

void Window::set_close() {
    glfwSetWindowShouldClose(this->window, true);
}
