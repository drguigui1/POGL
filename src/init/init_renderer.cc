#include "init_renderer.hh"
#include "init_lights.hh"

Renderer init_renderer3(const float& ratio) {
    // Lights
    shared_lights lights = init_lights();
    shared_lights house_lights = init_house_lights();
    shared_lights trunk_1_lights = init_trunk_lights();

    Renderer renderer(ratio);

    renderer.set_skybox(std::make_shared<Skybox>("data/skybox/fishpond"));
    renderer.set_skybox_shader(std::make_shared<Shader>("shaders/skybox.vs", "shaders/skybox.fs"));

    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", "data/models/house/house.obj", house_lights, false, 0.15f, glm::vec3(80.0f, -9.5f, 200.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", "data/models/fox/fox.obj", lights, true, 1.0f, glm::vec3(-18.0f, -1.5f, 13.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", "data/models/deer/deer.obj", lights, true, 1.0f, glm::vec3(-30.0f, -4.0f, 45.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", "data/models/wood/wood.obj", lights, true, 1.0f, glm::vec3(-19.0f, -4.9f, -20.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", "data/models/well/well.obj", lights, true, 1.0f, glm::vec3(-39.2f, -4.5f, 23.6f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", "data/models/fire/fire.obj", lights, true, 1.0f, glm::vec3(-4.0f, -4.35f, 16.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", "data/models/fire/firecamp.obj", lights, true, 1.0f, glm::vec3(15.0f, -4.35f, 5.0f));
    renderer.add_obj("shaders/obj_maps.vs", "shaders/obj_maps.fs", "data/models/road_sign/WoodRoadSign.obj", lights, true, 0.6f, glm::vec3(-7.0f, -7.35f, -26.0f));


    // Grass
    shared_obj grass = std::make_shared<Model>("data/models/grass/grass_flower.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", grass, lights, true, 1.0f, glm::vec3(5.0f, -4.0f, 30.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", grass, lights, true, 1.0f, glm::vec3(-20.0f, -4.5f, -15.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", grass, lights, true, 1.0f, glm::vec3(26.0f, -4.0f, -7.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", grass, lights, true, 1.0f, glm::vec3(5.0f, -4.0f, -27.0f));

    // Flower
    shared_obj flower = std::make_shared<Model>("data/models/flower/flower.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", flower, lights, true, 1.0f, glm::vec3(-17.0f, -2.25f, 5.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", flower, lights, true, 1.0f, glm::vec3(-23.4f, -1.0f, 10.5f));

    // Trunk 1
    shared_obj trunk_1 = std::make_shared<Model>("data/models/trunk/1/trunk.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", trunk_1, trunk_1_lights, false, 0.3f, glm::vec3(15.0f, -15.0f, 120.0f));

    // Trunk 2
    shared_obj trunk_2 = std::make_shared<Model>("data/models/trunk/2/trunk.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", trunk_2, lights, true, 1.0f, glm::vec3(26.0f, -4.5f, 3.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", trunk_2, lights, true, 1.0f, glm::vec3(-16.0f, -4.0f, -12.0f));

    // Rock
    shared_obj rock = std::make_shared<Model>("data/models/rock/rock.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", rock, lights, true, 1.0f, glm::vec3(39.2f, -4.5f, -33.6f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", rock, lights, true, 1.0f, glm::vec3(14.2f, -4.25f, -13.6f));

    // Tree 1
    shared_obj tree_1 = std::make_shared<Model>("data/models/tree/1/tree.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_1, lights, true, 1.0f, glm::vec3(3.0f, -5.0f, -5.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_1, lights, true, 1.0f, glm::vec3(-0.5f, -5.0f, -12.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_1, lights, true, 1.0f, glm::vec3(25.0f, -4.25f, 33.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_1, lights, true, 1.0f, glm::vec3(-30.0f, -4.5f, 2.5f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_1, lights, true, 1.0f, glm::vec3(-37.0f, -4.0f, 4.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_1, lights, true, 1.0f, glm::vec3(16.0f, -5.0f, -8.0f));

    // Tree 2
    shared_obj tree_2 = std::make_shared<Model>("data/models/tree/2/tree.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_2, lights, true, 1.0f, glm::vec3(-8.1f, -5.0f, -29.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_2, lights, true, 1.0f, glm::vec3(-38.1f, -4.8f, -13.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_2, lights, true, 1.0f, glm::vec3(-8.5f, -5.0f, -20.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_2, lights, true, 1.0f, glm::vec3(-1.6f, -5.0f, 30.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_2, lights, true, 1.0f, glm::vec3(-30.0f, -4.5f, -8.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_2, lights, true, 1.0f, glm::vec3(-32.7f, -4.5f, -44.7f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_2, lights, true, 1.0f, glm::vec3(34.0f, -5.0f, 39.0f));

    shared_obj tree_3 = std::make_shared<Model>("data/models/tree/3/tree.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_3, lights, true, 1.0f, glm::vec3(-10.0f, -5.0f, -1.7f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_3, lights, true, 1.0f, glm::vec3(-11.5f, -5.0f, -31.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_3, lights, true, 1.0f, glm::vec3(-41.0f, -5.0f, -15.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_3, lights, true, 1.0f, glm::vec3(-37.0f, -4.8f, -3.5f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_3, lights, true, 1.0f, glm::vec3(13.2f, -4.5f, -25.2f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_3, lights, true, 1.0f, glm::vec3(-40.0f, -3.0f, -28.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_3, lights, true, 1.0f, glm::vec3(28.0f, -5.0f, 43.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree_3, lights, true, 1.0f, glm::vec3(37.0f, -5.0f, 10.0f));

    return renderer;
}
