#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include <string>

#include "init.hh"
#include "shader.hh"

#include "window.hh"
#include "camera.hh"
#include "object.hh"
#include "init_obj.hh"
#include "texture.hh"

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(Window& window) {
    if (window.key_press(GLFW_KEY_ESCAPE) || window.key_press(GLFW_KEY_SPACE))
        window.set_close();

    if (window.key_press(GLFW_KEY_W))
        camera.process_keyboard(FORWARD, deltaTime);
    if (window.key_press(GLFW_KEY_S))
        camera.process_keyboard(BACKWARD, deltaTime);
    if (window.key_press(GLFW_KEY_A))
        camera.process_keyboard(LEFT, deltaTime);
    if (window.key_press(GLFW_KEY_D))
        camera.process_keyboard(RIGHT, deltaTime);
}

int main(int argc, char** argv) {
    unsigned int width, height;
    if (argc != 3) {
        width = 800;
        height = 600;
    } else {
        width = std::stoi(std::string(argv[1]));
        height = std::stoi(std::string(argv[2]));
    }

    // Init glfw / window / glew
    init_glfw();
    Window window = init_window(width, height, "Title");
    init_glew();

    // Enable z-buffer
    glEnable(GL_DEPTH_TEST);

    Texture texture("data/container.jpg");

    Shader shader("shaders/test.vs", "shaders/test.fs");
    Shader plane_shader("shaders/plane.vs", "shaders/plane.fs");
    Shader cube2_shader("shaders/cube_tex.vs", "shaders/cube_tex.fs");

    Object plane = create_plane();
    Object cube = create_cube();

    // Render loop
    while (!window.should_close()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        glm::mat4 model = glm::mat4(1.0f);
        //model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        shader.set_mat4("model", model);
        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), window.get_ratio(), 0.1f, 100.0f);
        shader.set_mat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.get_matrix_view();
        shader.set_mat4("view", view);

        shader.set_float("iTime", glfwGetTime());
        shader.set_float("width", width);
        shader.set_float("height", height);

        cube.draw();

        plane_shader.use();
        plane_shader.set_mat4("projection", projection);
        plane_shader.set_mat4("view", view);
        plane_shader.set_mat4("model", model);

        plane.draw();

        // draw another cube
        texture.use();
        cube2_shader.use();

        model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
        cube2_shader.set_mat4("projection", projection);
        cube2_shader.set_mat4("view", view);
        cube2_shader.set_mat4("model", model);

        cube.draw();

        window.swap_buffers();
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
