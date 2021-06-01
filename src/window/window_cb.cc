#include "window.hh"

#include "camera.hh"

float prev_x = 0;
float prev_y = 0;

bool mouse_cb_called = false;

static void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Window::set_framebuffer_size_cb() {
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
}

static void mouse_callback(GLFWwindow* window, double x, double y) {
    if (!mouse_cb_called) {
        prev_x = x;
        prev_y = y;
        mouse_cb_called = true;
        return;
    }

    camera.process_mouse_movement(x - prev_x, prev_y - y);

    prev_x = x;
    prev_y = y;

}

void Window::set_mouse_cb() {
    glfwSetCursorPosCallback(this->window, mouse_callback);
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.process_mouse_scroll(yoffset);
}

void Window::set_scroll_cb() {
    glfwSetScrollCallback(this->window, scroll_callback);
}
