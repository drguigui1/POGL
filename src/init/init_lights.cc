#include "init_lights.hh"

shared_lights init_lights(const glm::vec3 offset) {
    glm::vec3 l_color(1.0, 1.0, 1.0);

    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, offset + glm::vec3(3.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, offset + glm::vec3(-3.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, offset + glm::vec3(0.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);

    Lights lights;
    lights.set_directional_light(std::make_shared<DirectionalLight>(dir_light));
    lights.add_point_light(std::make_shared<PointLight>(p_light1));
    lights.add_point_light(std::make_shared<PointLight>(p_light2));
    lights.add_point_light(std::make_shared<PointLight>(p_light3));

    return std::make_shared<Lights>(lights);
}

shared_lights init_house_lights(const glm::vec3 offset) {
    glm::vec3 l_color(1.0, 1.0, 1.0);

    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, offset + glm::vec3(5.5f, 4.0f, 27.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, offset + glm::vec3(6.0f, 3.0f, 35.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, offset + glm::vec3(5.0f, 2.0f, 20.0f), 1.0f, 0.09f, 0.032f);

    Lights lights;
    lights.set_directional_light(std::make_shared<DirectionalLight>(dir_light));
    lights.add_point_light(std::make_shared<PointLight>(p_light1));
    lights.add_point_light(std::make_shared<PointLight>(p_light2));
    lights.add_point_light(std::make_shared<PointLight>(p_light3));

    return std::make_shared<Lights>(lights);
}

shared_lights init_trunk_lights(const glm::vec3 offset) {
    glm::vec3 l_color(1.0, 1.0, 1.0);

    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, offset + glm::vec3(-2.0f, 2.0f, 45.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, offset + glm::vec3(-6.0f, 2.0f, 30.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, offset + glm::vec3(-4.0f, 3.0f, 40.0f), 1.0f, 0.09f, 0.032f);

    Lights lights;
    lights.set_directional_light(std::make_shared<DirectionalLight>(dir_light));
    lights.add_point_light(std::make_shared<PointLight>(p_light1));
    lights.add_point_light(std::make_shared<PointLight>(p_light2));
    lights.add_point_light(std::make_shared<PointLight>(p_light3));

    return std::make_shared<Lights>(lights);
}

shared_lights init_museum_lights(const glm::vec3 offset) {
    glm::vec3 l_color(1.0, 1.0, 1.0);

    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(0.0f, 0.0f, -5.0f));
    PointLight p_light1(l_color, offset + glm::vec3(-2.0f, 3.0f, 1.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, offset + glm::vec3(-6.0f, 3.0f, 3.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, offset + glm::vec3(-4.0f, 4.0f, 4.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light4(l_color, offset + glm::vec3(-1.0f, 3.0f, 1.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light5(l_color, offset + glm::vec3(1.0f, 1.7f, 1.0f), 1.0f, 0.19f, 0.132f);

    Lights lights;
    lights.set_directional_light(std::make_shared<DirectionalLight>(dir_light));
    lights.add_point_light(std::make_shared<PointLight>(p_light1));
    lights.add_point_light(std::make_shared<PointLight>(p_light2));
    lights.add_point_light(std::make_shared<PointLight>(p_light3));
    lights.add_point_light(std::make_shared<PointLight>(p_light4));
    lights.add_point_light(std::make_shared<PointLight>(p_light5));

    return std::make_shared<Lights>(lights);
}

shared_lights init_museum_entrance_lights(const glm::vec3 offset) {
    glm::vec3 l_color(1.0, 1.0, 1.0);

    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, offset + glm::vec3(-9.0f, 5.0f, 30.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, offset + glm::vec3(-18.0f, 5.0f, 7.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, offset + glm::vec3(-12.0f, 5.0f, 7.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light4(l_color, offset + glm::vec3( -6.0f, 5.0f, 7.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light5(l_color, offset + glm::vec3(  0.0f, 5.0f, 7.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light6(l_color, offset + glm::vec3(  6.0f, 5.0f, 7.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light7(l_color, offset + glm::vec3( 12.0f, 5.0f, 7.0f), 1.0f, 0.09f, 0.032f);

    Lights lights;
    lights.set_directional_light(std::make_shared<DirectionalLight>(dir_light));
    lights.add_point_light(std::make_shared<PointLight>(p_light1));
    lights.add_point_light(std::make_shared<PointLight>(p_light2));
    lights.add_point_light(std::make_shared<PointLight>(p_light3));
    lights.add_point_light(std::make_shared<PointLight>(p_light4));
    lights.add_point_light(std::make_shared<PointLight>(p_light5));
    lights.add_point_light(std::make_shared<PointLight>(p_light6));
    lights.add_point_light(std::make_shared<PointLight>(p_light7));

    return std::make_shared<Lights>(lights);
}

shared_lights init_museum_wall_lights(const glm::vec3& offset) {
    glm::vec3 l_color(1.0, 1.0, 1.0);

    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, offset + glm::vec3(-12.0f, 5.0f, 7.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, offset + glm::vec3(-11.0f, 5.0f, -10.5f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, offset + glm::vec3(-7.0f, 5.0f, 0.5f), 1.0f, 0.09f, 0.032f);
    PointLight p_light4(l_color, offset + glm::vec3(-7.0f, 5.0f, 8.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light5(l_color, offset + glm::vec3(-10.0f, 5.0f, 20.0f), 1.0f, 0.09f, 0.032f);

    Lights lights;
    lights.set_directional_light(std::make_shared<DirectionalLight>(dir_light));
    lights.add_point_light(std::make_shared<PointLight>(p_light1));
    lights.add_point_light(std::make_shared<PointLight>(p_light2));
    lights.add_point_light(std::make_shared<PointLight>(p_light3));
    lights.add_point_light(std::make_shared<PointLight>(p_light4));
    lights.add_point_light(std::make_shared<PointLight>(p_light5));

    return std::make_shared<Lights>(lights);
}
