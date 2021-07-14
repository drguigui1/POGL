#include "lights.hh"

void Lights::add_point_light(shared_light light) {
    this->point_lights.push_back(light);
}

void Lights::send_data_to_shader(shared_shader shader, const glm::vec3& offset) const {
    // send directional light data
    this->directional_light->to_shader(shader, 0, offset);

    // send point lights data
    int nb_p_lights = this->point_lights.size();
    for (int i = 0; i < nb_p_lights; ++i)
        this->point_lights[i]->to_shader(shader, i, offset);

    // send the number of point lights
    shader->set_int("nbLights", nb_p_lights);
}
