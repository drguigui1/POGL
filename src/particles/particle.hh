#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <optional>

#include "shader.hh"

class Particle {
public:
    Particle();

    void update(float delta);

    /* Getters */
    glm::vec3 get_position() const { return position; }
    glm::vec3 get_velocity() const { return velocity; }
    glm::vec4 get_color() const { return color; }
    float get_scale() const { return scale; }
    std::optional<std::pair<float, glm::vec3>> get_rotation() const { return rotation; }
    float get_lifetime() const { return lifetime; }

    /* Setters */
    void set_position(const glm::vec3& v) { position = v; }
    void set_velocity(const glm::vec3& v) { velocity = v; }
    void set_color(const glm::vec4& v) { color = v; }
    void set_scale(const float& v) { scale = v; }
    void set_rotation(const std::pair<float, glm::vec3>& v) { rotation = v; }
    void set_rotation(const float& rad, const glm::vec3& ax) { rotation = std::make_pair(rad, ax); }
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
