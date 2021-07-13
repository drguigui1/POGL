#pragma once

#include <utility>

#include "renderer_object.hh"
#include "renderer_particles.hh"
#include "model.hh"
#include "skybox.hh"

class Renderer {
public:
    Renderer() = default;
    Renderer(const float& r);

    /* Methods */
    void render_skybox();
    void render_objs();
    void render_particles(const float& delta_time);

    void add_obj(shared_shader shader, shared_obj obj,
            shared_lights lights, const bool& cam,
            const float& scale, const glm::vec3& translate);
    void add_obj(const char* vertex_path, const char* fragment_path,
            const char* model_path, shared_lights sl, const bool& c,
            const float& s, const glm::vec3& t);
    void add_obj(const char* vertex_path, const char* fragment_path,
            shared_obj obj, shared_lights light, const bool& offset,
            const float& scale, const glm::vec3& translate);

    void add_particles(shared_shader sh, shared_particles p, shared_lights sl);

    /* Setters */
    void set_skybox(shared_skybox s) { skybox.first = s; }
    void set_skybox_shader(shared_shader s) { skybox.second = s; }

private:
    /* Attributes */
    std::pair<shared_skybox, shared_shader> skybox;
    std::vector<RendererObject> objs;
    std::vector<RendererParticles> particles;

    float ratio;
    float prev_frame;

};
