#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include <string>
#include <ctime>

#include "init.hh"
#include "shader.hh"

#include "window.hh"
#include "camera.hh"
#include "object.hh"
#include "init_obj.hh"
#include "texture.hh"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void processInput(Window& window, float time) {
    // Close window
    if (window.key_press(GLFW_KEY_ESCAPE) || window.key_press(GLFW_KEY_SPACE))
        window.set_close();

    // Camera movement
    if (window.key_press(GLFW_KEY_W))
        camera.process_keyboard(FORWARD, time);
    if (window.key_press(GLFW_KEY_S))
        camera.process_keyboard(BACKWARD, time);
    if (window.key_press(GLFW_KEY_A))
        camera.process_keyboard(LEFT, time);
    if (window.key_press(GLFW_KEY_D))
        camera.process_keyboard(RIGHT, time);

    // Wireframe mode
    if (window.key_press(GLFW_KEY_N))
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    if (window.key_press(GLFW_KEY_M))
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

int main(int argc, char** argv) {
    std::srand(std::time(nullptr));

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

    // Shaders
    Shader glob_shader("shaders/global.vs", "shaders/global.fs");
    Shader plane_shader("shaders/plane.vs", "shaders/plane.fs");
    Shader cube2_shader("shaders/cube_tex.vs", "shaders/cube_tex.fs");

    Object plane = create_plane2(0, 0, 20, 20, 0.1, 0.1);
    Object cube = create_cube();

    // timing
    float prev_frame = 0.0f;

    // Render loop
    while (!window.should_close()) {
        float curr_frame = glfwGetTime();

        // input
        processInput(window, curr_frame - prev_frame);
        prev_frame = curr_frame;

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), window.get_ratio(), 0.1f, 100.0f);
        glm::mat4 view = camera.get_matrix_view();

        glob_shader.use();

        // Glob cube
        glob_shader.set_mat4("projection", projection);
        glob_shader.set_mat4("model", model);
        glob_shader.set_mat4("view", view);

        glob_shader.set_float("iTime", glfwGetTime());
        glob_shader.set_float("width", width);
        glob_shader.set_float("height", height);

        cube.draw();

        // Plane
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
        cube2_shader.set_vec3("lightColor", 1.0f, 1.0f, 1.0f);
        cube2_shader.set_vec3("lightPos", 0.0f, 5.0f, 0.0f);

        cube.draw();

        window.swap_buffers();
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
