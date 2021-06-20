#pragma once

#include <memory>
#include <optional>

#include "particle.hh"
#include "object.hh"

class Particles {
public:
    Particles();
    Particles(const glm::vec3& cen,
            const glm::vec3& rad_min = glm::vec3(0.0f),
            const glm::vec3& rad_max = glm::vec3(1.0f));

    /* Methods */
    void generate_particles(unsigned int nb);
    void add_particle(const Particle& particle);

    void draw(Shader& shader, const glm::mat4& projection, const glm::mat4& view);
    void update(float delta);

    /* Setters */
    void set_center(const glm::vec3& c) { center = c; }
    void set_radius_min(const glm::vec3& r) { radius_min = r; }
    void set_radius_max(const glm::vec3& r) { radius_max = r; }
    void set_obj(std::shared_ptr<Object> o) { obj = o; }
    void set_velocity_min(const glm::vec3& v) { velocity_min = v; }
    void set_velocity_max(const glm::vec3& v) { velocity_max = v; }
    void set_scale_min(const float& v) { scale_min = v; }
    void set_scale_max(const float& v) { scale_max = v; }

    void set_rotation(const std::pair<float, glm::vec3>& r) { rotation = r; }
    void set_rotation(const float& rad, const glm::vec3& ax) { rotation = std::make_pair(rad, ax); }

private:
    /* Methods */
    shared_particle create_particle(float y) const;
    void set_new_particle_at(unsigned int& idx);

    /* Attributes */
    std::vector<shared_particle> particles;

    glm::vec3 center; // Position
    glm::vec3 radius_min;
    glm::vec3 radius_max;

    glm::vec3 velocity_min; // Velocity min
    glm::vec3 velocity_max; // Velocity max

    float scale_min; // Scale min
    float scale_max; // Scale max

    std::optional<std::pair<float, glm::vec3>> rotation;

    // Particle model
    std::shared_ptr<Object> obj;
};
