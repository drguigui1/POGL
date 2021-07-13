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

RendererObject create_renderer_obj(const char* vertex_path,
        const char* fragment_path, const char* model_path, shared_lights lights,
        const bool& cam, const float& scale, const glm::vec3& translate) {

    shared_shader shader = std::make_shared<Shader>(vertex_path, fragment_path);
    shared_obj model = std::make_shared<Model>(model_path);

    return RendererObject(shader, model, lights, cam, scale, translate);
}
