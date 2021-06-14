#include "particule.hh"


Particule::Particule()
    : position(glm::vec3(0.0f)), velocity(glm::vec3(0.0f, 0.5, 0.0f)), color(glm::vec4(1.0f)), lifetime(10.0f)
{}

Particule::Particule(const glm::vec3& pos, const glm::vec3& vel, const glm::vec4& col, const float& life)
    : position(pos), velocity(vel), color(col), lifetime(life)
{}

void Particule::update(float delta) {
    this->position -= this->velocity * delta;
    this->lifetime -= delta;
}
