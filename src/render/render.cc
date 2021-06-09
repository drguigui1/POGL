#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render.hh"

#include "shader.hh"

#include "camera.hh"
#include "object.hh"
#include "init_obj.hh"
#include "texture.hh"
#include "height_map.hh"
#include "save.hh"
#include "skybox.hh"

#include "noise.hh"
#include "noise2.hh"

#include "model.hh"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

unsigned int loadCubemap(std::vector<std::string> faces);

static void processInput(Window& window, float time) {
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

void render(Window& window, unsigned int width, unsigned int height) {
    Texture texture("data/container.jpg");

    // Shaders
    Shader glob_shader("shaders/global.vs", "shaders/global.fs");
    Shader plane_shader("shaders/plane_grad.vs", "shaders/plane_grad.fs");
    Shader cube2_shader("shaders/cube_tex.vs", "shaders/cube_tex.fs");

    //std::vector<float> height_map = generate_height_map(200, 200);
    //save::save_to_ppm_grayscale("height_map.ppm", height_map, 200, 200);

    // Create plane from height map
    //Object plane = create_plane_from_heightmap("height_map.ppm", 0, 0, 0.1, 0.1);

    Object plane = create_plane2(0, 0, 20, 20, 0.1, 0.1, Noise(5, NOISE));
    //plane.set_y_max(plane.get_y_max() / 2.0f);

    //Object plane = create_plane2(0, 0, 20, 20, 0.1, 0.1, ImprovedNoise());
    Object cube = create_cube();

    // timing
    float prev_frame = 0.0f;

    while (!window.should_close()) {
        float curr_frame = glfwGetTime();

        // input
        processInput(window, curr_frame - prev_frame);
        prev_frame = curr_frame;

        // render
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
        plane_shader.set_float("height", plane.get_y_max());

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
        cube2_shader.set_vec3("userPos", camera.get_position());

        cube.draw();

        window.swap_buffers();
        glfwPollEvents();
    }
}

void render2(Window& window, unsigned int, unsigned int) {
    // Shaders
    Shader plane_shader("shaders/plane_terrain.vs", "shaders/plane_terrain.fs");
    Shader cube2_shader("shaders/cube_tex.vs", "shaders/cube_tex.fs");
    Shader skybox_shader("shaders/skybox.vs", "shaders/skybox.fs");
    Shader obj_shader("shaders/obj.vs", "shaders/obj.fs");

    // Objects
    Object plane = create_plane(5);
    Object cube = create_cube();
    Skybox skybox("data/skybox/forest");
    //Skybox skybox("data/skybox/hornstulls");

    // Texture
    Texture texture("data/container.jpg");

    const std::string path = "data/models/soccer_ball/football_ball_OBJ.obj";
    auto ball = Model(path);

    // timing
    float prev_frame = 0.0f;
    while (!window.should_close()) {
        float curr_frame = glfwGetTime();

        // input
        processInput(window, curr_frame - prev_frame);
        prev_frame = curr_frame;

        // render
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), window.get_ratio(), 0.1f, 100.0f);
        glm::mat4 view = camera.get_matrix_view();

        // Plane
        plane_shader.use();
        plane_shader.set_mat4("projection", projection);
        plane_shader.set_mat4("view", view);
        plane_shader.set_mat4("model", model);
        plane_shader.set_float("iTime", curr_frame);

        //plane.draw();

        // draw another cube
        texture.use();
        cube2_shader.use();

        model = glm::translate(model, glm::vec3(3.0f, 0.0f, 0.0f));
        cube2_shader.set_mat4("projection", projection);
        cube2_shader.set_mat4("view", view);
        cube2_shader.set_mat4("model", model);
        cube2_shader.set_vec3("lightColor", 1.0f, 1.0f, 1.0f);
        cube2_shader.set_vec3("lightPos", 0.0f, 5.0f, 0.0f);
        cube2_shader.set_vec3("userPos", camera.get_position());

        //cube.draw();

        ball.draw(obj_shader);
        obj_shader.set_mat4("projection", projection);
        obj_shader.set_mat4("view", view);
        obj_shader.set_mat4("model", model);

        obj_shader.set_vec3("lightColor", 1.0f, 1.0f, 1.0f);
        obj_shader.set_vec3("lightPos", 0.0f, 5.0f, 0.0f);
        obj_shader.set_vec3("userPos", camera.get_position());

        // Skybox
        skybox_shader.use();
        view = glm::mat4(glm::mat3(camera.get_matrix_view()));
        skybox_shader.set_mat4("view", view);
        skybox_shader.set_mat4("projection", projection);

        skybox.draw();

        window.swap_buffers();
        glfwPollEvents();
    }
}
