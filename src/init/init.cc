#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>

#include "init.hh"

#include "light.hh"

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

Lights init_lights() {
    glm::vec3 l_color(1.0, 1.0, 1.0);

    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, glm::vec3(3.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, glm::vec3(-3.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, glm::vec3(0.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);

    Lights lights;
    lights.add_directional_light(dir_light);
    lights.add_point_light(p_light1);
    lights.add_point_light(p_light2);
    lights.add_point_light(p_light3);

    return lights;
}

Lights init_house_lights() {
    glm::vec3 l_color(1.0, 1.0, 1.0);

    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, glm::vec3(5.5f, 4.0f, 27.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, glm::vec3(6.0f, 3.0f, 35.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, glm::vec3(5.0f, 2.0f, 20.0f), 1.0f, 0.09f, 0.032f);

    Lights lights;
    lights.add_directional_light(dir_light);
    lights.add_point_light(p_light1);
    lights.add_point_light(p_light2);
    lights.add_point_light(p_light3);

    return lights;
}
