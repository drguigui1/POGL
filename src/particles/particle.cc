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
