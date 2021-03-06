#include "init_renderer.hh"
#include "init_lights.hh"
#include "init_obj.hh"

Renderer init_renderer_forest(const float& ratio, const glm::vec3) {

    std::cout << "\n\tInit renderer FOREST" << std::endl;

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

Renderer init_renderer_museum(const float& ratio, const glm::vec3 offset) {
    std::cout << "\n\tInit renderer MUSEUM" << std::endl;

    // Lights
    shared_lights lights = init_museum_lights();
    shared_lights entrance_lights = init_museum_entrance_lights();
    shared_lights wall_lights1 = init_museum_wall_lights(offset + glm::vec3(0.0f));
    shared_lights wall_lights2 = init_museum_wall_lights(offset + glm::vec3(19.0f, 0.0f, -12.5f));

    Renderer renderer(ratio);

    renderer.set_skybox(std::make_shared<Skybox>("data/skybox/lazarus"));
    renderer.set_skybox_shader(std::make_shared<Shader>("shaders/skybox.vs", "shaders/skybox.fs"));

    // ile the pacque 1
    shared_obj statue3 = std::make_shared<Model>("data/models/statue/3/statue3.obj");
    renderer.add_obj("shaders/obj_maps.vs", "shaders/obj_maps.fs", statue3, lights, true, 1.0f, offset + glm::vec3(-17.5f, -0.5f, -12.0f));

    // venus de milo
    shared_obj statue1 = std::make_shared<Model>("data/models/statue/1/venus_milo_procedural.obj");
    renderer.add_obj("shaders/marble.vs", "shaders/marble.fs", statue1, lights, true, 1.0f, offset + glm::vec3(-13.5f, -0.35f, -12.0f));

    // other statue
    shared_obj statue4 = std::make_shared<Model>("data/models/statue/4/statue.obj");
    renderer.add_obj("shaders/obj_maps.vs", "shaders/obj_maps.fs", statue4, lights, true, 1.0f, offset + glm::vec3(-9.0f, -0.4f, -12.0f));

    // thai statue
    shared_obj statue2 = std::make_shared<Model>("data/models/statue/2/Thai.obj");
    renderer.add_obj("shaders/marble.vs", "shaders/marble.fs", statue2, lights, true, 1.0f, offset + glm::vec3(-5.0f, -0.5f, -12.0f));

    // ile de pacque 2
    shared_obj statue5 = std::make_shared<Model>("data/models/statue/5/untitled.obj");
    renderer.add_obj("shaders/obj_maps.vs", "shaders/obj_maps.fs", statue5, lights, true, 1.0f, offset + glm::vec3(-2.0f, -1.0f, -12.0f));

    // painting
    shared_obj painting = std::make_shared<Model>("data/models/painting/painting.obj");
    renderer.add_obj("shaders/obj_maps.vs", "shaders/obj_maps.fs", painting, lights, true, 1.0f, offset + glm::vec3(-10.7f, 2.0f, 6.0f));

    //shared_obj museum = std::make_shared<Model>("data/models/museum/museum.obj");
    //renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", museum, lights, true, 2.5f, offset + glm::vec3(0.0f, 0.0f, 0.0f));

    // Entrance
    shared_obj entrance = std::make_shared<Model>("data/models/entrance/entrance.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", entrance, entrance_lights, false, 1.0f, offset + glm::vec3(-10.0f, -0.45f, 14.0f));

    // Wall 1
    shared_obj wall = std::make_shared<Model>("data/models/entrance/entrance2.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", wall, wall_lights1, false, 1.0f, offset + glm::vec3(0.0f, -0.45f, 0.0f));

    // Wall 2
    shared_obj wall2 = std::make_shared<Model>("data/models/entrance/entrance3.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", wall2, wall_lights2, false, 1.0f, offset + glm::vec3(18.325f, -0.45f, 12.5f));

    // Barrier
    shared_obj barrier = std::make_shared<Model>("data/models/barrier/barrier.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", barrier, lights, true, 1.0f, offset + glm::vec3(-17.0f, -0.35f, -9.5f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", barrier, lights, true, 1.0f, offset + glm::vec3(-11.0f, -0.35f, -9.5f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", barrier, lights, true, 1.0f, offset + glm::vec3( -5.0f, -0.35f, -9.5f));

    // Pillar
    shared_obj pillar = std::make_shared<Model>("data/models/pillar/pillar.obj");
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", pillar, lights, true, 1.0f, offset + glm::vec3(-1.0f, -0.35f, 13.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", pillar, lights, true, 1.0f, offset + glm::vec3(-17.0f, -0.35f, 13.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", pillar, lights, true, 1.0f, offset + glm::vec3(1.0f, -0.35f, 13.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", pillar, lights, true, 1.0f, offset + glm::vec3(17.0f, -0.35f, 13.0f));

    // Bench
    shared_obj bench = std::make_shared<Model>("data/models/bench/bench.obj");
    renderer.add_obj("shaders/obj_maps.vs", "shaders/obj_maps.fs", bench, lights, true, 1.0f, offset + glm::vec3(-5.0f, -0.5f, 12.65f));
    renderer.add_obj("shaders/obj_maps.vs", "shaders/obj_maps.fs", bench, lights, true, 1.0f, offset + glm::vec3( 5.0f, -0.5f, 12.65f));
    renderer.add_obj("shaders/obj_maps.vs", "shaders/obj_maps.fs", bench, lights, true, 1.0f, offset + glm::vec3( 11.0f, -0.5f, 12.65f));

    return renderer;
}

static void add_tree_symetric(Renderer& renderer, shared_obj tree1, shared_obj tree2, shared_lights lights, const glm::vec3 offset, const glm::vec3& pos) {
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree1, lights, true, 1.0f, offset + pos);
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", tree2, lights, true, 1.0f, offset + glm::vec3(-pos.x, pos.y, pos.z));
}

Renderer init_renderer_particles(const float& ratio, const glm::vec3 offset) {

    std::cout << "\n\tInit renderer PARTICLES" << std::endl;

    // Lights
    shared_lights lights = init_lights();

    Renderer renderer(ratio);

    renderer.set_skybox(std::make_shared<Skybox>("data/skybox/mix_forest_meadow"));
    renderer.set_skybox_shader(std::make_shared<Shader>("shaders/skybox.vs", "shaders/skybox.fs"));

    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", "data/models/snowman/snowman.obj", lights, true, 1.0f, offset + glm::vec3(2.0f, -0.5f, 3.0f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", "data/models/hut/hut.obj", lights, true, 1.0f, offset + glm::vec3(7.1f, -0.5f, 1.5f));
    renderer.add_obj("shaders/obj.vs", "shaders/obj.fs", "data/models/bear/bear.obj", lights, true, 1.0f, offset + glm::vec3(3.8f, -0.5f, 7.11f));
    renderer.add_obj("shaders/obj_maps.vs", "shaders/obj_maps.fs", "data/models/picnic_table/picnic_table.obj", lights, true, 1.0f, offset + glm::vec3(-3.1f, -0.5f, 2.5f));
    renderer.add_obj("shaders/obj_maps.vs", "shaders/obj_maps.fs", "data/models/camp/camp.obj", lights, true, 1.0f, offset + glm::vec3(-7.1f, 0.0f, 2.5f));

    // Pine tree with/without snow
    shared_obj pine_snow = std::make_shared<Model>("data/models/pine/pine_tree_snow.obj");
    shared_obj pine = std::make_shared<Model>("data/models/pine/pine_tree.obj");

    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(8.7f, -0.5f, -10.65f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(14.4f, -0.5f, -10.65f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(14.4f, -0.5f, 10.65f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(3.2f, -0.5f, 10.65f));

    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(10.0f, -0.5f, 0.0f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(2.6f, -0.5f, -9.4f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(4.3f, -0.5f, -6.1f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(4.9f, -0.5f, -10.1f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(4.1f, -0.5f, -7.7f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(6.7f, -0.5f, -9.1f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(8.9f, -0.5f, -8.7f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(11.7f, -0.5f, -9.7f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(10.9f, -0.5f, -7.5f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(11.83f, -0.5f, -8.3f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(13.9f, -0.5f, -9.65f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(3.3f, -0.5f, -2.3f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(7.1f, -0.5f, -3.6f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(7.8f, -0.5f, -7.6f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(8.1f, -0.5f, -4.6f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(6.4f, -0.5f, -6.2f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(8.8f, -0.5f, -6.6f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(5.1f, -0.5f, -4.7f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(12.1f, -0.5f, -2.6f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(9.3f, -0.5f, -2.6f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(14.1f, -0.5f, -3.9f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(13.8f, -0.5f, -1.8f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(12.5f, -0.5f, -5.8f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(10.8f, -0.5f, -3.8f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(7.5f, -0.5f, -2.1f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(5.2f, -0.5f, 9.1f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(6.7f, -0.5f, 9.4f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(8.4f, -0.5f, 7.6f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(11.4f, -0.5f, 3.1f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(9.2f, -0.5f, 3.9f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(12.4f, -0.5f, -0.2f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(11.0f, -0.5f, 0.77f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(10.7f, -0.5f, 4.77f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(14.1f, -0.5f, 1.77f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(12.1f, -0.5f, 4.56f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(13.76f, -0.5f, 7.56f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(14.3f, -0.5f, 3.96f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(12.84f, -0.5f, 5.28f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(11.54f, -0.5f, 6.71f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(11.4f, -0.5f, 8.51f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(10.15f, -0.5f, 9.47f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(9.27f, -0.5f, 10.52f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(13.15f, -0.5f, 9.38f));
    add_tree_symetric(renderer, pine_snow, pine, lights, offset, glm::vec3(9.15f, -0.5f, 5.47f));

    // Pine tree with some snow
    shared_obj pine_half_snow = std::make_shared<Model>("data/models/pine/pine_tree_half_snow.obj");
    add_tree_symetric(renderer, pine_half_snow, pine_half_snow, lights, offset, glm::vec3(1.91f, -0.5f, -7.06f));
    add_tree_symetric(renderer, pine_half_snow, pine_half_snow, lights, offset, glm::vec3(0.68f, -0.5f, -8.51f));
    add_tree_symetric(renderer, pine_half_snow, pine_half_snow, lights, offset, glm::vec3(1.24f, -0.5f, -4.05f));
    add_tree_symetric(renderer, pine_half_snow, pine_half_snow, lights, offset, glm::vec3(5.71f, -0.5f, -2.63f));
    add_tree_symetric(renderer, pine_half_snow, pine_half_snow, lights, offset, glm::vec3(0.74f, -0.5f, -5.52f));
    add_tree_symetric(renderer, pine_half_snow, pine_half_snow, lights, offset, glm::vec3(0.85f, -0.5f, 9.31f));

    // Drop particles
    shared_obj drop = std::make_shared<Model>("data/models/drop/drop.obj");
    shared_particles drop_particles = create_particles(1000, drop,
            offset + glm::vec3(-17.0f, 0.0f, -11.25f),
            offset + glm::vec3(0.0f, 7.0f, 11.25f),
            0.05f, 0.10f);
    shared_shader drop_particles_shader = std::make_shared<Shader>("shaders/particles.vs", "shaders/particles.fs");
    renderer.add_particles(drop_particles_shader, drop_particles, lights);

    // Snowflake particles
    shared_obj snowflake = std::make_shared<Model>("data/models/snowflake/snowflake.obj");
    shared_particles snowflake_particles = create_particles(1000, snowflake,
            offset + glm::vec3(-2.0f, 0.0f, -11.25f),
            offset + glm::vec3(15.0f, 7.0f, 11.25f),
            0.015f, 0.05f, -55.0f);
    shared_shader snowflake_particles_shader = std::make_shared<Shader>("shaders/particles.vs", "shaders/particles.fs");
    renderer.add_particles(snowflake_particles_shader, snowflake_particles, lights);

    return renderer;
}
