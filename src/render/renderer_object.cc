#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer_object.hh"

RendererObject::RendererObject(shared_shader sh, shared_obj so, shared_lights sl, const bool& c, const float& s, const glm::vec3& t)
    : shader(sh), object(so), lights(sl), cam(c), scale(s), translate(t)
{}

void RendererObject::render(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& cam_pos) {
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
    model = glm::translate(model, translate);

    object->draw(shader);

    shader->set_projection_view_model(projection, view, model);
    shader->set_vec3("userPos", cam_pos);

    if (cam)
        lights->send_data_to_shader(shader, cam_pos);
    else
        lights->send_data_to_shader(shader);
}

