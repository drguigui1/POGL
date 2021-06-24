#pragma once

#include <vector>

#include "light.hh"
#include "shader.hh"

class Lights {
public:
    Lights() = default;
    void add_directional_light(DirectionalLight light);
    void add_point_light(PointLight light);
    void send_data_to_shader(Shader& shader);

private:
    std::vector<PointLight> point_lights;
    DirectionalLight directional_light;

};