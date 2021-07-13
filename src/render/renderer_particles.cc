#include "renderer_particles.hh"

RendererParticles::RendererParticles(shared_shader sh, shared_particles sp, shared_lights sl)
    : shader(sh), particles(sp), lights(sl)
{}

void RendererParticles::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& cam_pos, const float& delta_time) {
    shader->use();
    particles->draw(shader, lights, projection, view, cam_pos);
    particles->update(delta_time);
}
