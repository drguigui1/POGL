#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "init.hh"
#include "init_lights.hh"
#include "init_obj.hh"
#include "init_renderer.hh"

#include "render.hh"
#include "render_utils.hh"

#include "camera.hh"
#include "height_map.hh"
#include "save.hh"

#include "noise.hh"
#include "noise2.hh"

//Camera camera(glm::vec3(0.0f, 0.0f, 50.0f));
Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));

enum SceneType {
    FOREST,
    MUSEUM,
    RAIN_SNOW
};

static void process_input(Window& window, float time, bool& enable_bubbles, bool& switch_scene) {
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

    // Bubble
    if (window.key_press(GLFW_KEY_B))
        enable_bubbles = true;
    if (window.key_press(GLFW_KEY_V))
        enable_bubbles = false;

    // Switch scene
    if (window.key_press(GLFW_KEY_C))
        switch_scene = true;
    if (window.key_press(GLFW_KEY_X))
        switch_scene = false;
}

static void switch_renderer(const glm::vec3& cam_pos, SceneType& scene) {
    if (scene == FOREST
            && cam_pos.x >= 10.15f && cam_pos.x <= 15.72f
            && cam_pos.z >= 25.42f && cam_pos.z <= 34.13f) {
        scene = RAIN_SNOW; // FIXME: MUSEUM
    }

    if (scene == MUSEUM && cam_pos.x == 15.0f) // FIXME: condition to change scene
        scene = RAIN_SNOW;

    if (scene == RAIN_SNOW && cam_pos.x <= -15.0f)
        scene = FOREST;
}

static void gl_clear_update() {
    // Background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void render(Window& window) {
    // Variables
    const float ratio = window.get_ratio();
    bool enable_bubbles = true;
    bool switch_scene = true;
    float prev_frame = 0.0f;
    SceneType scene = FOREST;

    // Shared lights / objects
    shared_lights lights = init_lights();
    Object bubble = create_plane_geom();

    /* Scene 1 */
    Renderer renderer1 = init_renderer1(ratio);

    // Textures
    Texture tex_heightmap("data/images/heightmap.jpg");
    Texture tex_snow("data/images/snow.jpg");
    Texture tex_rock("data/images/rock.jpg");
    Texture tex_grass("data/images/grass2.jpg");
    Texture tex_dirt("data/images/dirt.jpg");
    Texture tex_path("data/images/path.jpg");

    // Terrain
    Shader terrain_shader("shaders/terrain/terrain.vs", "shaders/terrain/terrain.fs");
    Object terrain = create_heightmap_plane(glm::vec2(0.0), 96, 96, 0.25, 0.25);

    // Set textures to terrain shader
    terrain_shader.use();
    terrain_shader.set_int("heightmap", 0);
    terrain_shader.set_int("snow", 1);
    terrain_shader.set_int("rock", 2);
    terrain_shader.set_int("grass", 3);
    terrain_shader.set_int("dirt", 4);
    terrain_shader.set_int("path", 5);

    // Bubble
    Shader bubble_rise_shader("shaders/bubble/bubble.vs", "shaders/bubble/bokeh_rising.fs", "shaders/bubble/bubble.gs");

    /* Scene 2 */
    // TODO

    /* Scene 3 */
    Renderer renderer3 = init_renderer3(ratio);

    // Winter plane
    Texture winter("data/images/winter.jpg");
    Object winter_plane = create_plane(7.5, 7.5f, 1.5f);
    Shader winter_plane_shader("shaders/ground/plane.vs", "shaders/ground/plane.fs");
    winter_plane_shader.use();
    winter_plane_shader.set_int("texture1", 0);

    // Grass plane
    Texture grass("data/images/grass.jpg");
    Object grass_plane = create_plane(7.5, -7.5f, 1.5f);
    Shader grass_plane_shader("shaders/ground/plane.vs", "shaders/ground/plane.fs");
    grass_plane_shader.use();
    grass_plane_shader.set_int("texture1", 0);

    // Bubble
    Shader bubble_shines_shader("shaders/bubble/bubble.vs", "shaders/bubble/shines.fs", "shaders/bubble/bubble.gs");

    // Render loop
    while (!window.should_close()) {
        float curr_frame = glfwGetTime();
        const glm::vec3 cam_pos = camera.get_position();

        process_input(window, curr_frame - prev_frame, enable_bubbles, switch_scene);
        gl_clear_update();

        /* Render opaque objects */
        switch (scene) {
        case FOREST:
            // Terrain
            tex_heightmap.use(0);
            tex_snow.use(1);
            tex_rock.use(2);
            tex_grass.use(3);
            tex_dirt.use(4);
            tex_path.use(5);

            render_terrain(terrain_shader, ratio, terrain);
            lights->send_data_to_shader(terrain_shader, cam_pos);

            // Objs & Skybox
            renderer1.render_objs();
            renderer1.render_skybox();
            break;

        default:
            render_plane(winter_plane_shader, ratio, winter_plane, winter);
            render_plane(grass_plane_shader, ratio, grass_plane, grass);

            // Objs & Particles & Skybox
            renderer3.render_objs();
            renderer3.render_particles(curr_frame - prev_frame);
            renderer3.render_skybox();
            break;
        }

        /* Render transparent objects */
        glDepthMask(false); // disable z-testing
        if (enable_bubbles) {
            switch (scene) {
            case FOREST:
                render_bubble(bubble_rise_shader, ratio, bubble, curr_frame, window.get_width(), window.get_height());
                break;
            default:
                render_bubble(bubble_shines_shader, ratio, bubble, curr_frame, window.get_width(), window.get_height());
                break;
            }
        }
        glDepthMask(true); // enable z-testing

        prev_frame = curr_frame;
        window.swap_buffers();
        glfwPollEvents();

        if (switch_scene)
            switch_renderer(cam_pos, scene);

        std::cout << "Cam position: " << cam_pos.x << ' ' << cam_pos.y << ' ' << cam_pos.z << std::endl;
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
    Shader bubble_shader("shaders/bubble/bubble.vs", "shaders/bubble/bokeh.fs", "shaders/bubble/bubble.gs");
    //Shader bubble_shader("shaders/bubble/bubble.vs", "shaders/bubble/bokeh_rising.fs", "shaders/bubble/bubble.gs");
    //Shader bubble_shader("shaders/bubble/bubble.vs", "shaders/bubble/shines.fs", "shaders/bubble/bubble.gs");
    Shader bubble_shader2("shaders/bubble/bubble.vs", "shaders/bubble/rising.fs", "shaders/bubble/bubble.gs");
    Shader grid_shader("shaders/grid/grid.vs", "shaders/grid/grid.fs", "shaders/grid/grid.gs");

    // Objects
    Object plane = create_plane(5);
    ///Object cube = create_cube();
    Skybox skybox("data/skybox/forest");
    //Skybox skybox("data/skybox/hornstulls");
    //Object signal = create_signal_geom();
    Object bubble = create_plane_geom();
    Object bubble2 = create_plane_geom();
    Object grid = create_plane_geom();

    // Lights
    Lights lights;
    glm::vec3 l_color(1.0, 1.0, 1.0);
    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, glm::vec3(3.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, glm::vec3(-3.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, glm::vec3(0.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    lights.set_directional_light(std::make_shared<DirectionalLight>(dir_light));
    lights.add_point_light(std::make_shared<PointLight>(p_light1));
    lights.add_point_light(std::make_shared<PointLight>(p_light2));
    lights.add_point_light(std::make_shared<PointLight>(p_light3));

    const std::string cuctus1_path = "data/models/cuctus/1/cuctus1.obj";
    auto cuctus1 = Model(cuctus1_path);

    const std::string cube_path = "data/models/cube/cube.obj";
    auto marble_cube = Model(cube_path);

    //const std::string ball_path = "data/models/soccer_ball/football_ball_OBJ.obj";
    //Model ball(ball_path);

    const float window_ratio = window.get_ratio();
    bool enable_bubbles = true;
    bool switch_scene = false;
    // timing
    float prev_frame = 0.0f;
    while (!window.should_close()) {
        float curr_frame = glfwGetTime();

        process_input(window, curr_frame - prev_frame, enable_bubbles, switch_scene);
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

        // Ball
        //render_ball(obj_shader, window_ratio, ball);

        // Skybox
        render_skybox(skybox_shader, window_ratio, skybox);

        /* Render transparent objects */
        glDepthMask(false); // disable z-testing
        render_bubble(bubble_shader, window_ratio, bubble, curr_frame, window.get_width(), window.get_height());
        render_bubble(bubble_shader2, window_ratio, bubble2, curr_frame, window.get_width(), window.get_height());
        //render_grid(grid_shader, window_ratio, grid, curr_frame, window.get_width(), window.get_height());
        glDepthMask(true); // enable z-testing

        prev_frame = curr_frame;
        window.swap_buffers();
        glfwPollEvents();
    }
}

void render_forest(Window& window) {
    // Variables
    const float ratio = window.get_ratio();
    bool enable_bubbles = true;
    bool switch_scene = false;
    float prev_frame = 0.0f;

    // Shared lights / objects
    shared_lights lights = init_lights();
    Object bubble = create_plane_geom();

    Renderer renderer1 = init_renderer1(ratio);

    // Textures
    Texture tex_heightmap("data/images/heightmap.jpg");
    Texture tex_snow("data/images/snow.jpg");
    Texture tex_rock("data/images/rock.jpg");
    Texture tex_grass("data/images/grass2.jpg");
    Texture tex_dirt("data/images/dirt.jpg");
    Texture tex_path("data/images/path.jpg");

    // Terrain
    Shader terrain_shader("shaders/terrain/terrain.vs", "shaders/terrain/terrain.fs");
    Object terrain = create_heightmap_plane(glm::vec2(0.0), 96, 96, 0.25, 0.25);

    // Set textures to terrain shader
    terrain_shader.use();
    terrain_shader.set_int("heightmap", 0);
    terrain_shader.set_int("snow", 1);
    terrain_shader.set_int("rock", 2);
    terrain_shader.set_int("grass", 3);
    terrain_shader.set_int("dirt", 4);
    terrain_shader.set_int("path", 5);

    // Bubble
    Shader bubble_rise_shader("shaders/bubble/bubble.vs", "shaders/bubble/bokeh_rising.fs", "shaders/bubble/bubble.gs");

    // Render loop
    while (!window.should_close()) {
        float curr_frame = glfwGetTime();
        const glm::vec3 cam_pos = camera.get_position();

        process_input(window, curr_frame - prev_frame, enable_bubbles, switch_scene);
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
        lights->send_data_to_shader(terrain_shader, cam_pos);

        // Objs & Skybox
        renderer1.render_objs();
        renderer1.render_skybox();

        /* Render transparent objects */
        glDepthMask(false); // disable z-testing
        if (enable_bubbles)
            render_bubble(bubble_rise_shader, ratio, bubble, curr_frame, window.get_width(), window.get_height());
        glDepthMask(true); // enable z-testing

        prev_frame = curr_frame;
        window.swap_buffers();
        glfwPollEvents();

        std::cout << "Cam position: " << cam_pos.x << ' ' << cam_pos.y << ' ' << cam_pos.z << std::endl;
    }

}

void render4(Window& window) {
    // Variables
    const float ratio = window.get_ratio();
    bool enable_bubbles = true;
    bool switch_scene = false;
    float prev_frame = 0.0f;

    // shaders
    Shader skybox_shader("shaders/skybox.vs", "shaders/skybox.fs");
    Shader plane_shader("shaders/ground/plane.vs", "shaders/ground/plane.fs");
    Shader obj_shader1("shaders/obj_maps.vs", "shaders/obj_maps.fs");
    Shader obj_shader2("shaders/obj_maps.vs", "shaders/obj_maps.fs");
    Shader obj_shader3("shaders/obj_maps.vs", "shaders/obj_maps.fs");
    Shader marble_shader1("shaders/marble.vs", "shaders/marble.fs");
    Shader marble_shader2("shaders/marble.vs", "shaders/marble.fs");

    // Objects
    Object plane = create_plane(5);
    Skybox skybox("data/skybox/forest");
    Model statue1("data/models/statue/1/venus_milo_procedural.obj");
    Model statue2("data/models/statue/2/Thai.obj");
    Model statue3("data/models/statue/3/statue3.obj");
    Model statue4("data/models/statue/4/statue.obj");
    Model statue5("data/models/statue/5/untitled.obj");

    // Textures
    Texture ground("data/images/floor_texture4.jpg");

    shared_lights lights = init_museum_lights();

    plane_shader.use();
    plane_shader.set_int("texture1", 0);

    // Render loop
    while (!window.should_close()) {
        float curr_frame = glfwGetTime();
        const glm::vec3 cam_pos = camera.get_position();

        process_input(window, curr_frame - prev_frame, enable_bubbles, switch_scene);
        gl_clear_update();

        // Plane
        render_plane(plane_shader, ratio, plane, ground);

        // obj
        render_obj(marble_shader1, ratio, statue1, 0.4f, glm::vec3(0.0f, -1.0f, 0.0f));
        lights->send_data_to_shader(marble_shader1, cam_pos);

        render_obj(marble_shader2, ratio, statue2, 0.4f, glm::vec3(1.5f, -1.0f, 0.0f));
        lights->send_data_to_shader(marble_shader2, cam_pos);

        render_obj(obj_shader1, ratio, statue3, 0.15f, glm::vec3(-4.0f, -2.0f, 0.0f));
        lights->send_data_to_shader(obj_shader1, cam_pos);

        render_obj(obj_shader2, ratio, statue4, 0.4, glm::vec3(-4.0f, -1.0f, 0.0f));
        lights->send_data_to_shader(obj_shader2, cam_pos);

        render_obj(obj_shader3, ratio, statue5, 1.0, glm::vec3(-5.0f, -1.0f, 0.0f));
        lights->send_data_to_shader(obj_shader3, cam_pos);

        // Skybox
        render_skybox(skybox_shader, ratio, skybox);

        prev_frame = curr_frame;
        window.swap_buffers();
        glfwPollEvents();
    }
}

void render_rain_snow(Window& window) {
    // Variables
    const float ratio = window.get_ratio();
    bool enable_bubbles = true;
    bool switch_scene = false;
    float prev_frame = 0.0f;

    Renderer renderer3 = init_renderer3(ratio);

    // Lights
    shared_lights lights = init_lights();


    // Winter plane
    Texture winter("data/images/winter.jpg");
    Object winter_plane = create_plane(7.5, 7.5f, 1.5f);
    Shader winter_plane_shader("shaders/ground/plane.vs", "shaders/ground/plane.fs");
    winter_plane_shader.use();
    winter_plane_shader.set_int("texture1", 0);

    // Grass plane
    Texture grass("data/images/grass.jpg");
    Object grass_plane = create_plane(7.5, -7.5f, 1.5f);
    Shader grass_plane_shader("shaders/ground/plane.vs", "shaders/ground/plane.fs");
    grass_plane_shader.use();
    grass_plane_shader.set_int("texture1", 0);

    // Bubble
    Object bubble = create_plane_geom();
    Shader bubble_shines_shader("shaders/bubble/bubble.vs", "shaders/bubble/shines.fs", "shaders/bubble/bubble.gs");

    // Render loop
    while (!window.should_close()) {
        float curr_frame = glfwGetTime();
        process_input(window, curr_frame - prev_frame, enable_bubbles, switch_scene);
        gl_clear_update();

        /* Render opaque objects */
        render_plane(winter_plane_shader, ratio, winter_plane, winter);
        render_plane(grass_plane_shader, ratio, grass_plane, grass);

        renderer3.render_objs();
        renderer3.render_particles(curr_frame - prev_frame);

        // Skybox
        renderer3.render_skybox();

        /* Render transparent objects */
        glDepthMask(false); // disable z-testing
        if (enable_bubbles)
            render_bubble(bubble_shines_shader, ratio, bubble, curr_frame, window.get_width(), window.get_height());
        glDepthMask(true); // enable z-testing

        prev_frame = curr_frame;
        window.swap_buffers();
        glfwPollEvents();
    }
}
