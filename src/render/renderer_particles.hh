#pragma once

#include "lights.hh"
#include "shader.hh"
#include "particles.hh"

class RendererParticles {
public:
    RendererParticles() = default;
    RendererParticles(shared_shader sh, shared_particles p, shared_lights sl);

    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& cam_pos, const float& delta_time);

private:
    shared_shader shader;
    shared_particles particles;
    shared_lights lights;
};

