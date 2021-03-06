#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hh"
#include "renderer.hh"
#include "render_utils.hh"

Renderer::Renderer(const float& r)
    : ratio(r), prev_frame(0)
{}

void Renderer::render_skybox() {
    auto sky = skybox.first;
    auto shader = skybox.second;

    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(glm::mat3(camera.get_matrix_view()));
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 50.0f, 50.0f));

    shader->use();

    shader->set_projection_view_model(projection, view, model);
    shader->set_vec3("userPos", camera.get_position());

    sky->draw();
}

void Renderer::render_objs() {
    const glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    const glm::mat4 view = camera.get_matrix_view();
    const glm::vec3 cam_pos = camera.get_position();
    for (auto& obj : objs)
        obj.render(projection, view, cam_pos);
}

void Renderer::render_particles(const float& delta_time) {
    const glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    const glm::mat4 view = camera.get_matrix_view();
    const glm::vec3 cam_pos = camera.get_position();
    for (auto& particle : particles)
        particle.render(projection, view, cam_pos, delta_time);
}

void Renderer::add_obj(shared_shader shader, shared_obj obj, shared_lights light,
        const bool& offset, const float& scale, const glm::vec3& translate) {
    this->objs.emplace_back(shader, obj, light, offset, scale, translate);
}

void Renderer::add_obj(const char* vertex_path, const char* fragment_path,
        const char* model_path, shared_lights light, const bool& offset,
        const float& scale, const glm::vec3& translate) {
    shared_shader shader = std::make_shared<Shader>(vertex_path, fragment_path);
    shared_obj obj = std::make_shared<Model>(model_path);
    this->objs.emplace_back(shader, obj, light, offset, scale, translate);
}

void Renderer::add_obj(const char* vertex_path, const char* fragment_path,
        shared_obj obj, shared_lights light, const bool& offset,
        const float& scale, const glm::vec3& translate) {
    shared_shader shader = std::make_shared<Shader>(vertex_path, fragment_path);
    this->objs.emplace_back(shader, obj, light, offset, scale, translate);
}

void Renderer::add_particles(shared_shader sh, shared_particles p, shared_lights sl) {
    this->particles.emplace_back(sh, p, sl);
}
