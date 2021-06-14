#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "shader.hh"

class Particule {
public:
    Particule();
    Particule(const glm::vec3& pos, const glm::vec3& vel, const glm::vec4& col, const float& life);

    void update(float delta);

    /* Getters */
    glm::vec3 get_position() const { return position; }
    glm::vec3 get_velocity() const { return velocity; }
    glm::vec4 get_color() const { return color; }
    float get_lifetime() const { return lifetime; }

    /* Setters */
    void set_position(const glm::vec3& v) { position = v; }
    void set_velocity(const glm::vec3& v) { velocity = v; }
    void set_color(const glm::vec4& v) { color = v; }
    void set_lifetime(const float& v) { lifetime = v; }

private:
    /* Attributes */
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec4 color;

    float lifetime;
};

using shared_particule = std::shared_ptr<Particule>;
