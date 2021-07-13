#pragma once

#include "lights.hh"
#include "object.hh"

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

