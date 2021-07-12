#include "init_lights.hh"

Lights init_lights() {
    glm::vec3 l_color(1.0, 1.0, 1.0);

    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, glm::vec3(3.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, glm::vec3(-3.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, glm::vec3(0.0f, 3.0f, 0.0f), 1.0f, 0.09f, 0.032f);

    Lights lights;
    lights.add_directional_light(dir_light);
    lights.add_point_light(p_light1);
    lights.add_point_light(p_light2);
    lights.add_point_light(p_light3);

    return lights;
}

Lights init_house_lights() {
    glm::vec3 l_color(1.0, 1.0, 1.0);

    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, glm::vec3(5.5f, 4.0f, 27.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, glm::vec3(6.0f, 3.0f, 35.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, glm::vec3(5.0f, 2.0f, 20.0f), 1.0f, 0.09f, 0.032f);

    Lights lights;
    lights.add_directional_light(dir_light);
    lights.add_point_light(p_light1);
    lights.add_point_light(p_light2);
    lights.add_point_light(p_light3);

    return lights;
}

Lights init_trunk_lights() {
    glm::vec3 l_color(1.0, 1.0, 1.0);

    DirectionalLight dir_light(glm::vec3(0.8f, 0.8f, 0.8f), glm::vec3(-5.0f, -5.0f, -5.0f));
    PointLight p_light1(l_color, glm::vec3(-2.0f, 2.0f, 45.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light2(l_color, glm::vec3(-6.0f, 2.0f, 30.0f), 1.0f, 0.09f, 0.032f);
    PointLight p_light3(l_color, glm::vec3(-4.0f, 3.0f, 40.0f), 1.0f, 0.09f, 0.032f);

    Lights lights;
    lights.add_directional_light(dir_light);
    lights.add_point_light(p_light1);
    lights.add_point_light(p_light2);
    lights.add_point_light(p_light3);

    return lights;
}
