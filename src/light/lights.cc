#include "lights.hh"

void Lights::add_directional_light(const DirectionalLight& light) {
    this->directional_light = light;
}

void Lights::add_point_light(const PointLight& light) {
    this->point_lights.push_back(light);
}

void Lights::send_data_to_shader(Shader& shader, const glm::vec3& offset) {
    // send directional light data
    shader.set_vec3("dirLight.lightColor", this->directional_light.light_color);
    shader.set_vec3("dirLight.dir", this->directional_light.light_dir);

    // send point lights data
    int nb_p_lights = this->point_lights.size();
    for (int i = 0; i < nb_p_lights; ++i) {
        PointLight p_light = this->point_lights[i];
        std::string str_i = std::to_string(i);

        shader.set_vec3("pointLights[" + str_i + "].lightColor", p_light.light_color);
        shader.set_vec3("pointLights[" + str_i + "].pos", p_light.light_pos + offset);
        shader.set_float("pointLights[" + str_i + "].kc", p_light.light_kc);
        shader.set_float("pointLights[" + str_i + "].kl", p_light.light_kl);
        shader.set_float("pointLights[" + str_i + "].kq", p_light.light_kq);
    }

    // send the number of point lights
    shader.set_int("nbLights", nb_p_lights);
}
