#pragma once

#include <vector>

#include "light.hh"
#include "shader.hh"

class Lights {
public:
    Lights() = default;
    void add_directional_light(const DirectionalLight& light);
    void add_point_light(const PointLight& light);
    void send_data_to_shader(Shader& shader, const glm::vec3& offset = glm::vec3(0.0f));

private:
    std::vector<PointLight> point_lights;
    DirectionalLight directional_light;

};
