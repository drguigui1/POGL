#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render.hh"

//#include "shader.hh"
#include "render_utils.hh"

#include "camera.hh"
#include "init_obj.hh"
#include "height_map.hh"
#include "save.hh"

#include "noise.hh"
#include "noise2.hh"

#include "lights.hh"

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

static void process_input(Window& window, float time) {
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

static void gl_clear_update() {
    // Background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render(Window& window) {
    float prev_frame = 0.0f;
    const float window_ratio = window.get_ratio();

    // Textures
    Texture texture("data/images/container.jpg");

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

    while (!window.should_close()) {
        float curr_frame = glfwGetTime();

        // input
        process_input(window, curr_frame - prev_frame);

        // render
        gl_clear_update();

        // Glob cube
        render_global_cube(glob_shader, window_ratio, cube);

        // Plane
        render_noised_plane(plane_shader, window_ratio, plane);

        // draw another cube
        render_container_cube(cube2_shader, window_ratio, cube, texture);

        prev_frame = curr_frame;
        window.swap_buffers();
        glfwPollEvents();
    }
}

void render2(Window& window) {
    // Shaders
    Shader plane_shader("shaders/plane_terrain.vs", "shaders/plane_terrain.fs");
    Shader cube2_shader("shaders/cube_tex.vs", "shaders/cube_tex.fs");
    Shader skybox_shader("shaders/skybox.vs", "shaders/skybox.fs");
    Shader obj_shader_map("shaders/obj_maps.vs", "shaders/obj_maps.fs");
    Shader obj_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader particles_shader("shaders/particles.vs", "shaders/particles.fs");
    Shader marble_shader("shaders/marble.vs", "shaders/marble.fs");

    // Objects
    Object plane = create_plane(5);
    ///Object cube = create_cube();
    Skybox skybox("data/skybox/forest");
    //Skybox skybox("data/skybox/hornstulls");

    // Lights
    Lights lights;
    glm::vec3 l_color(1.0, 1.0, 1.0);
    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, glm::vec3(3.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, glm::vec3(-3.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, glm::vec3(0.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    lights.add_directional_light(dir_light);
    lights.add_point_light(p_light1);
    lights.add_point_light(p_light2);
    lights.add_point_light(p_light3);

    // Texture
    Texture texture("data/images/container.jpg");

    const std::string cuctus1_path = "data/models/cuctus/1/cuctus1.obj";
    auto cuctus1 = Model(cuctus1_path);

    const std::string cube_path = "data/models/cube/cube.obj";
    auto cube = Model(cube_path);

    //const std::string backpack_path = "data/models/backpack/backpack.obj";
    //auto backpack = Model(backpack_path);

    //const std::string ball_path = "data/models/soccer_ball/football_ball_OBJ.obj";
    //Model ball(ball_path);

    Particles snowflake_particles = create_snowflake_particles();

    const float window_ratio = window.get_ratio();
    // timing
    float prev_frame = 0.0f;
    while (!window.should_close()) {
        float curr_frame = glfwGetTime();

        // input
        process_input(window, curr_frame - prev_frame);

        // render
        gl_clear_update();

        glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), window_ratio, 0.1f, 100.0f);
        glm::mat4 view = camera.get_matrix_view();

        // Plane
        render_plane(plane_shader, window_ratio, plane);

        // Backpack
        //render_backpack(obj_shader_map, window_ratio, backpack);

        // cuctus
        cuctus1.draw(obj_shader);
        auto model_cuctus = glm::translate(glm::mat4(1), glm::vec3(0.0f, 0.5f, 0.0f));
        model_cuctus = glm::scale(model_cuctus, glm::vec3(0.6f, 0.6f, 0.6f));
        obj_shader.set_mat4("projection", projection);
        obj_shader.set_mat4("view", view);
        obj_shader.set_mat4("model", model_cuctus);

        lights.send_data_to_shader(obj_shader);

        obj_shader.set_vec3("userPos", camera.get_position());

        // cube
        cube.draw(marble_shader);
        auto model_cube = glm::translate(glm::mat4(1), glm::vec3(1.5f, 0.0f, 0.0f));
        model_cube = glm::scale(model_cube, glm::vec3(0.3f, 0.3f, 0.3f));
        marble_shader.set_mat4("projection", projection);
        marble_shader.set_mat4("view", view);
        marble_shader.set_mat4("model", model_cube);

        lights.send_data_to_shader(marble_shader);

        marble_shader.set_vec3("userPos", camera.get_position());

        //particules_shader.use();
        //particules_shader.set_mat4("projection", projection);
        //particules_shader.set_mat4("view", view);
        //particules_shader.set_mat4("model", model);
        //particules.draw(particules_shader);

        //cube2_shader.use();

        //particules_shader.use();

        //ball.draw(obj_shader);
        //obj_shader.set_mat4("projection", projection);
        //obj_shader.set_mat4("view", view);
        //obj_shader.set_mat4("model", model);

        //obj_shader.set_vec3("lightColor", 1.0f, 1.0f, 1.0f);
        //obj_shader.set_vec3("lightPos", 0.0f, 5.0f, 0.0f);

        // Particles
        render_particles(particles_shader, window_ratio, snowflake_particles, curr_frame - prev_frame);

        // Ball
        //render_ball(obj_shader, window_ratio, ball);

        // Skybox
        render_skybox(skybox_shader, window_ratio, skybox);

        prev_frame = curr_frame;
        window.swap_buffers();
        glfwPollEvents();
    }
}
