#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "init.hh"
#include "init_lights.hh"
#include "init_obj.hh"

#include "render.hh"
#include "render_utils.hh"

#include "camera.hh"
#include "height_map.hh"
#include "save.hh"

#include "noise.hh"
#include "noise2.hh"

Camera camera(glm::vec3(0.0f, 0.0f, 50.0f));

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

    // Camera speed
    if (window.key_press(GLFW_KEY_PAGE_UP))
        camera.increase_speed();
    if (window.key_press(GLFW_KEY_PAGE_DOWN))
        camera.decrease_speed();

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
    Texture texture("data/images/snowflake.JPEG");

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
    //Shader signal_shader("shaders/signal_shader.vs", "shaders/signal_shader.fs", "shaders/signal_shader.gs");
    //Shader bubble_shader("shaders/bubble/bubble.vs", "shaders/bubble/bokeh.fs", "shaders/bubble/bubble.gs");
    //Shader bubble_shader("shaders/bubble/bubble.vs", "shaders/bubble/bokeh_rising.fs", "shaders/bubble/bubble.gs");
    //Shader bubble_shader("shaders/bubble/bubble.vs", "shaders/bubble/shines.fs", "shaders/bubble/bubble.gs");
    //Shader bubble_shader("shaders/bubble/bubble.vs", "shaders/bubble/rising.fs", "shaders/bubble/bubble.gs");
    Shader grid_shader("shaders/grid/grid.vs", "shaders/grid/grid.fs", "shaders/grid/grid.gs");

    // Objects
    Object plane = create_plane(5);
    ///Object cube = create_cube();
    Skybox skybox("data/skybox/forest");
    //Skybox skybox("data/skybox/hornstulls");
    //Object signal = create_signal_geom();
    //Object bubble = create_plane_geom();
    Object grid = create_plane_geom();

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

    const std::string cuctus1_path = "data/models/cuctus/1/cuctus1.obj";
    auto cuctus1 = Model(cuctus1_path);

    const std::string cube_path = "data/models/cube/cube.obj";
    auto marble_cube = Model(cube_path);

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

        process_input(window, curr_frame - prev_frame);
        gl_clear_update();

        /* Render opaque objects */

        // Signal
        //render_signal(signal_shader, window_ratio, signal, curr_frame);

        // Plane
        render_plane(plane_shader, window_ratio, plane);

        // Backpack
        //render_backpack(obj_shader_map, window_ratio, backpack);

        // Cuctus
        render_cuctus(obj_shader, window_ratio, cuctus1);
        lights.send_data_to_shader(obj_shader);

        // cube
        render_marble_cube(marble_shader, window_ratio, marble_cube);
        lights.send_data_to_shader(marble_shader);

        // Particles
        render_particles(particles_shader, window_ratio, snowflake_particles, curr_frame - prev_frame);

        // Ball
        //render_ball(obj_shader, window_ratio, ball);

        // Skybox
        render_skybox(skybox_shader, window_ratio, skybox);

        /* Render transparent objects */
        glDepthMask(false); // disable z-testing
        //render_bubble(bubble_shader, window_ratio, bubble, curr_frame, window.get_width(), window.get_height());
        render_grid(grid_shader, window_ratio, grid, curr_frame, window.get_width(), window.get_height());
        glDepthMask(true); // enable z-testing

        prev_frame = curr_frame;
        window.swap_buffers();
        glfwPollEvents();
    }
}

void render3(Window& window) {
    // Variables
    const float ratio = window.get_ratio();
    float prev_frame = 0.0f;

    // Shaders
    Shader skybox_shader("shaders/skybox.vs", "shaders/skybox.fs");
    Shader terrain_shader("shaders/terrain/terrain.vs", "shaders/terrain/terrain.fs");
    Shader tree_1_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_2_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_3_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_4_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_5_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_6_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_7_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_8_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_9_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_10_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_11_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_12_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_13_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_14_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_15_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_16_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_17_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_18_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_19_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_20_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader tree_21_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader house_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader trunk_1_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader trunk_2_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader trunk_3_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader grass_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader grass_2_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader grass_3_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader grass_4_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader fire_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader firecamp_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader fox_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader deer_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader wood_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader well_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader rock_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader rock_2_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader flower_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader flower_2_shader("shaders/obj.vs", "shaders/obj.fs");
    Shader road_sign_shader("shaders/obj_maps.vs", "shaders/obj_maps.fs");

    // Objects
    Skybox skybox("data/skybox/fishpond");

    Object terrain = create_heightmap_plane(glm::vec2(0.0), 96, 96, 0.25, 0.25);
    Model tree_1("data/models/tree/1/tree.obj");
    Model tree_2("data/models/tree/2/tree.obj");
    Model tree_3("data/models/tree/3/tree.obj");
    Model road_sign("data/models/road_sign/WoodRoadSign.obj");
    Model house("data/models/house/house.obj");
    Model trunk_1("data/models/trunk/1/trunk.obj");
    Model trunk_2("data/models/trunk/2/trunk.obj");
    Model grass("data/models/grass/grass_flower.obj");
    Model fire("data/models/fire/fire.obj");
    Model firecamp("data/models/fire/firecamp.obj");
    Model fox("data/models/fox/fox.obj");
    Model deer("data/models/deer/deer.obj");
    Model wood("data/models/wood/wood.obj");
    Model well("data/models/well/well.obj");
    Model rock("data/models/rock/rock.obj");
    Model flower("data/models/flower/flower.obj");

    // Textures
    Texture tex_heightmap("data/images/heightmap.jpg");
    Texture tex_snow("data/images/snow.jpg");
    Texture tex_rock("data/images/rock.jpg");
    Texture tex_grass("data/images/grass2.jpg");
    Texture tex_dirt("data/images/dirt.jpg");
    Texture tex_path("data/images/path.jpg");

    // Lights
    Lights lights = init_lights();
    Lights house_lights = init_house_lights();
    Lights trunk_lights = init_trunk_lights();

    // Set textures to shader
    terrain_shader.use();
    terrain_shader.set_int("heightmap", 0);
    terrain_shader.set_int("snow", 1);
    terrain_shader.set_int("rock", 2);
    terrain_shader.set_int("grass", 3);
    terrain_shader.set_int("dirt", 4);
    terrain_shader.set_int("path", 5);

    // Render loop
    while (!window.should_close()) {
        float curr_frame = glfwGetTime();
        const glm::vec3 cam_pos = camera.get_position();

        process_input(window, curr_frame - prev_frame);
        gl_clear_update();

        /* Render opaque objects */

        // Terrain
        tex_heightmap.use(0);
        tex_snow.use(1);
        tex_rock.use(2);
        tex_grass.use(3);
        tex_dirt.use(4);
        tex_path.use(5);

        render_terrain(terrain_shader, ratio, terrain);
        lights.send_data_to_shader(terrain_shader, cam_pos);

        // Trees
        render_obj(tree_1_shader, ratio, tree_1, 1.0f, glm::vec3(3.0f, -5.0f, -5.0f));
        lights.send_data_to_shader(tree_1_shader, cam_pos);

        render_obj(tree_2_shader, ratio, tree_1, 1.0f, glm::vec3(-0.5f, -5.0f, -12.0f));
        lights.send_data_to_shader(tree_2_shader, cam_pos);

        render_obj(tree_3_shader, ratio, tree_3, 1.0f, glm::vec3(-10.0f, -5.0f, -1.7f));
        lights.send_data_to_shader(tree_3_shader, cam_pos);

        render_obj(tree_4_shader, ratio, tree_2, 1.0f, glm::vec3(-8.5f, -5.0f, -20.0f));
        lights.send_data_to_shader(tree_4_shader, cam_pos);

        render_obj(tree_5_shader, ratio, tree_2, 1.0f, glm::vec3(-1.6f, -5.0f, 30.0f));
        lights.send_data_to_shader(tree_5_shader, cam_pos);

        render_obj(tree_6_shader, ratio, tree_1, 1.0f, glm::vec3(25.0f, -4.25f, 33.0f));
        lights.send_data_to_shader(tree_6_shader, cam_pos);

        render_obj(tree_7_shader, ratio, tree_3, 1.0f, glm::vec3(-11.5f, -5.0f, -31.0f));
        lights.send_data_to_shader(tree_7_shader, cam_pos);

        render_obj(tree_8_shader, ratio, tree_2, 1.0f, glm::vec3(-8.1f, -5.0f, -29.0f));
        lights.send_data_to_shader(tree_8_shader, cam_pos);

        render_obj(tree_9_shader, ratio, tree_2, 1.0f, glm::vec3(-38.1f, -4.8f, -13.0f));
        lights.send_data_to_shader(tree_9_shader, cam_pos);

        render_obj(tree_10_shader, ratio, tree_3, 1.0f, glm::vec3(-41.0f, -5.0f, -15.0f));
        lights.send_data_to_shader(tree_10_shader, cam_pos);

        render_obj(tree_11_shader, ratio, tree_3, 1.0f, glm::vec3(-37.0f, -4.8f, -3.5f));
        lights.send_data_to_shader(tree_11_shader, cam_pos);

        render_obj(tree_12_shader, ratio, tree_1, 1.0f, glm::vec3(-30.0f, -4.5f, 2.5f));
        lights.send_data_to_shader(tree_12_shader, cam_pos);

        render_obj(tree_13_shader, ratio, tree_1, 1.0f, glm::vec3(-37.0f, -4.0f, 4.0f));
        lights.send_data_to_shader(tree_13_shader, cam_pos);

        render_obj(tree_14_shader, ratio, tree_2, 1.0f, glm::vec3(-30.0f, -4.5f, -8.0f));
        lights.send_data_to_shader(tree_14_shader, cam_pos);

        render_obj(tree_15_shader, ratio, tree_2, 1.0f, glm::vec3(-32.7f, -4.5f, -44.7f));
        lights.send_data_to_shader(tree_15_shader, cam_pos);

        render_obj(tree_16_shader, ratio, tree_3, 1.0f, glm::vec3(13.2f, -4.5f, -25.2f));
        lights.send_data_to_shader(tree_16_shader, cam_pos);

        render_obj(tree_17_shader, ratio, tree_3, 1.0f, glm::vec3(-40.0f, -3.0f, -28.0f));
        lights.send_data_to_shader(tree_17_shader, cam_pos);

        render_obj(tree_18_shader, ratio, tree_1, 1.0f, glm::vec3(16.0f, -5.0f, -8.0f));
        lights.send_data_to_shader(tree_18_shader, cam_pos);

        render_obj(tree_19_shader, ratio, tree_2, 1.0f, glm::vec3(34.0f, -5.0f, 39.0f));
        lights.send_data_to_shader(tree_19_shader, cam_pos);

        render_obj(tree_20_shader, ratio, tree_3, 1.0f, glm::vec3(28.0f, -5.0f, 43.0f));
        lights.send_data_to_shader(tree_20_shader, cam_pos);

        render_obj(tree_21_shader, ratio, tree_3, 1.0f, glm::vec3(37.0f, -5.0f, 10.0f));
        lights.send_data_to_shader(tree_21_shader, cam_pos);

        // House
        render_house(house_shader, ratio, house);
        house_lights.send_data_to_shader(house_shader);

        // Road sign
        render_road_sign(road_sign_shader, ratio, road_sign);

        // Trunks
        render_obj(trunk_1_shader, ratio, trunk_1, 0.3f, glm::vec3(15.0f, -15.0f, 120.0f));
        trunk_lights.send_data_to_shader(trunk_1_shader);

        render_obj(trunk_2_shader, ratio, trunk_2, 1.0f, glm::vec3(26.0f, -4.5f, 3.0f));
        trunk_lights.send_data_to_shader(trunk_2_shader);

        render_obj(trunk_3_shader, ratio, trunk_2, 1.0f, glm::vec3(-16.0f, -4.0f, -12.0f));
        trunk_lights.send_data_to_shader(trunk_3_shader);

        // Grass
        render_obj(grass_shader, ratio, grass, 1.0f, glm::vec3(5.0f, -4.0f, 30.0f));
        lights.send_data_to_shader(grass_shader, cam_pos);

        render_obj(grass_2_shader, ratio, grass, 1.0f, glm::vec3(-20.0f, -4.5f, -15.0f));
        lights.send_data_to_shader(grass_2_shader, cam_pos);

        render_obj(grass_3_shader, ratio, grass, 1.0f, glm::vec3(26.0f, -4.0f, -7.0f));
        lights.send_data_to_shader(grass_3_shader, cam_pos);

        render_obj(grass_4_shader, ratio, grass, 1.0f, glm::vec3(5.0f, -4.0f, -27.0f));
        lights.send_data_to_shader(grass_4_shader, cam_pos);

        // Fire
        render_obj(fire_shader, ratio, fire, 1.0f, glm::vec3(-4.0f, -4.35f, 16.0f));
        lights.send_data_to_shader(fire_shader, cam_pos);

        render_obj(firecamp_shader, ratio, firecamp, 1.0f, glm::vec3(15.0f, -4.35f, 5.0f));
        lights.send_data_to_shader(firecamp_shader, cam_pos);

        // Fox
        render_obj(fox_shader, ratio, fox, 1.0f, glm::vec3(-18.0f, -1.5f, 13.0f));
        lights.send_data_to_shader(fox_shader, cam_pos);

        // Deer
        render_obj(deer_shader, ratio, deer, 1.0f, glm::vec3(-30.0f, -4.0f, 45.0f));
        lights.send_data_to_shader(deer_shader, cam_pos);

        // Wood
        render_obj(wood_shader, ratio, wood, 1.0f, glm::vec3(-19.0f, -4.9f, -20.0f));
        lights.send_data_to_shader(wood_shader, cam_pos);

        // Well
        render_obj(well_shader, ratio, well, 1.0f, glm::vec3(-39.2f, -4.5f, 23.6f));
        lights.send_data_to_shader(well_shader, cam_pos);

        // Rock
        render_obj(rock_shader, ratio, rock, 1.0f, glm::vec3(39.2f, -4.25f, -33.6f));
        lights.send_data_to_shader(rock_shader, cam_pos);

        render_obj(rock_2_shader, ratio, rock, 1.0f, glm::vec3(14.2f, -4.25f, -13.6f));
        lights.send_data_to_shader(rock_2_shader, cam_pos);

        // Flower
        render_obj(flower_shader, ratio, flower, 1.0f, glm::vec3(-17.0f, -2.25f, 5.0f));
        lights.send_data_to_shader(flower_shader, cam_pos);

        render_obj(flower_2_shader, ratio, flower, 1.0f, glm::vec3(-23.4f, -1.0f, 10.5f));
        lights.send_data_to_shader(flower_2_shader, cam_pos);

        // Skybox
        render_skybox(skybox_shader, ratio, skybox);

        /* Render transparent objects */
        glDepthMask(false); // disable z-testing
        glDepthMask(true); // enable z-testing

        prev_frame = curr_frame;
        window.swap_buffers();
        glfwPollEvents();

        //std::cout << "Cam position: " << cam_pos.x << ' ' << cam_pos.y << ' ' << cam_pos.z << std::endl;
    }
}

void render4(Window& window) {
    // Variables
    const float ratio = window.get_ratio();
    float prev_frame = 0.0f;

    // shaders
    Shader skybox_shader("shaders/skybox.vs", "shaders/skybox.fs");
    Shader plane_shader("shaders/ground/plane.vs", "shaders/ground/plane.fs");
    Shader obj_shader("shaders/obj_maps.vs", "shaders/obj_maps.fs");
    Shader marble_shader("shaders/marble.vs", "shaders/marble.fs");

    // Objects
    Object plane = create_plane(5);
    Skybox skybox("data/skybox/forest");
    Model statue("data/models/statue/1/venus_milo_procedural.obj");

    // Textures
    Texture ground("data/images/floor_texture4.jpg");

    Lights lights = init_lights();

    plane_shader.use();
    plane_shader.set_int("texture1", 0);

    // Render loop
    while (!window.should_close()) {
        float curr_frame = glfwGetTime();
        const glm::vec3 cam_pos = camera.get_position();

        process_input(window, curr_frame - prev_frame);
        gl_clear_update();

        // Plane
        render_plane(plane_shader, ratio, plane, ground);

        // obj
        render_obj(marble_shader, ratio, statue, 0.3f, glm::vec3(0.0f, -2.0f, 0.0f));
        lights.send_data_to_shader(marble_shader, cam_pos);

        // Skybox
        render_skybox(skybox_shader, ratio, skybox);

        prev_frame = curr_frame;
        window.swap_buffers();
        glfwPollEvents();
    }
}
