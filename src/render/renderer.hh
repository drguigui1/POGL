#pragma once

#include <tuple>
#include <utility>

#include "lights.hh"
#include "model.hh"
#include "skybox.hh"

class RendererObject {
public:
    RendererObject() = default;
    RendererObject(shared_shader sh, shared_obj so, shared_lights sl,
            const bool& c, const float& s, const glm::vec3& t);

    void render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& cam_pos);

private:
    shared_shader shader;
    shared_obj object;
    shared_lights lights;
    bool cam; // Is lights stuck to camera

    float scale;
    glm::vec3 translate;
};

class Renderer {
public:
    Renderer() = default;
    Renderer(const float& r);

    /* Methods */
    void render_skybox();
    void render_objs();
    void add_obj(shared_shader shader, shared_obj obj,
            shared_lights lights, const bool& cam,
            const float& scale, const glm::vec3& translate);
    void add_obj(const char* vertex_path, const char* fragment_path,
            const char* model_path, shared_lights sl, const bool& c,
            const float& s, const glm::vec3& t);
    void add_obj(const char* vertex_path, const char* fragment_path,
            shared_obj obj, shared_lights light, const bool& offset,
            const float& scale, const glm::vec3& translate);
    void add_obj(const RendererObject& obj);

    /* Setters */
    void set_skybox(shared_skybox s) { skybox.first = s; }
    void set_skybox_shader(shared_shader s) { skybox.second = s; }

private:
    /* Attributes */
    std::pair<shared_skybox, shared_shader> skybox;
    std::vector<RendererObject> objs;

    float ratio;
    float prev_frame;

};
