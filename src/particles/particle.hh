#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <optional>

#include "shader.hh"

class Particle {
public:
    Particle();

    /* Methods */
    void update(float delta);
    bool is_alive() const;
    glm::mat4 get_model() const;

    /* Setters */
    void set_position(const glm::vec3& v) { position = v; }
    void set_velocity(const glm::vec3& v) { velocity = v; }
    void set_color(const glm::vec4& v) { color = v; }
    void set_scale(const float& v) { scale = v; }
    void set_rotation(const std::pair<float, glm::vec3>& v) { rotation = v; }
    void set_lifetime(const float& v) { lifetime = v; }

private:
    /* Attributes */
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec4 color;
    float scale;
    std::optional<std::pair<float, glm::vec3>> rotation;

    float lifetime;
};

using shared_particle = std::shared_ptr<Particle>;
