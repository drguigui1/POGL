#pragma once

#include <vector>

#include "light.hh"
#include "shader.hh"

class Lights {
public:
    Lights() = default;

    /* Methods */
    void add_point_light(shared_light light);
    void send_data_to_shader(Shader& shader, const glm::vec3& offset = glm::vec3(0.0f)) const;
    void send_data_to_shader(shared_shader shader, const glm::vec3& offset = glm::vec3(0.0f)) const;

    /* Setters */
    void set_directional_light(shared_light light) { this->directional_light = light; };

private:
    /* Attributes */
    std::vector<shared_light> point_lights; // std::vector<std::shared_ptr<PointLight>>
    shared_light directional_light; // std::shared_ptr<DirectionalLight>
};

using shared_lights = std::shared_ptr<Lights>;
