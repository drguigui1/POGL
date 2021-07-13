#pragma once

#include <memory>
#include <optional>

#include "particle.hh"
#include "object.hh"
#include "lights.hh"

class Particles {
public:
    Particles() = default;
    Particles(shared_obj o);

    /* Methods */
    void generate_particles(const unsigned int& nb);
    void add_particle(const Particle& particle);

    void draw(shared_shader shader, shared_lights lights, const glm::mat4& projection, const glm::mat4& view, const glm::vec3& cam_pos);
    void update(float delta);

    /* Setters */
    void set_obj(std::shared_ptr<Object>& o) { obj = o; }

    void set_position_min(const glm::vec3& p) { position_min = p; }
    void set_position_max(const glm::vec3& p) { position_max = p; }

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
    shared_obj obj; // Particles models

    glm::vec3 position_min; // Position min
    glm::vec3 position_max; // Position max

    glm::vec3 velocity_min; // Velocity min
    glm::vec3 velocity_max; // Velocity max

    float scale_min; // Scale min
    float scale_max; // Scale max

    std::optional<std::pair<float, glm::vec3>> rotation;

    std::vector<shared_particle> particles;
};
