#include <glm/gtc/matrix_transform.hpp>

#include "particle.hh"

Particle::Particle()
    : position(glm::vec3(0.0f)),
    velocity(glm::vec3(0.0f, 0.5, 0.0f)),
    color(glm::vec4(1.0f)),
    scale(1.0f),
    rotation({}),
    lifetime(10.0f)
{}

void Particle::update(float delta) {
    this->position -= this->velocity * delta;
    this->lifetime -= delta;
}

bool Particle::is_alive(const glm::vec3& pos_min, const glm::vec3& pos_max) const {
    if (this->position.x < pos_min.x || this->position.x > pos_max.x)
        return false;

    if (this->position.z < pos_min.z || this->position.z > pos_max.z)
        return false;

    return this->position.y > pos_min.y - 0.5f;
}

glm::mat4 Particle::get_model() const {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(scale));

    if (rotation.has_value())
        model = glm::rotate(model, rotation.value().first, rotation.value().second);

    return model;
}
