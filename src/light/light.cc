#include "light.hh"

Light::Light(const glm::vec3& c)
    : light_color(c)
{}

PointLight::PointLight(const glm::vec3& l_color,
                       const glm::vec3& l_pos,
                       float l_kc,
                       float l_kl,
                       float l_kq)
    : Light(l_color),
      light_pos(l_pos),
      light_kc(l_kc),
      light_kl(l_kl),
      light_kq(l_kq)
{}

void PointLight::to_shader(Shader& shader, const int& i, const glm::vec3 offset) const {
    std::string str_i = std::to_string(i);

    shader.set_vec3("pointLights[" + str_i + "].lightColor", light_color);
    shader.set_vec3("pointLights[" + str_i + "].pos", light_pos + offset);
    shader.set_float("pointLights[" + str_i + "].kc", light_kc);
    shader.set_float("pointLights[" + str_i + "].kl", light_kl);
    shader.set_float("pointLights[" + str_i + "].kq", light_kq);
}

void PointLight::to_shader(shared_shader shader, const int& i, const glm::vec3 offset) const {
    std::string str_i = std::to_string(i);

    shader->set_vec3("pointLights[" + str_i + "].lightColor", light_color);
    shader->set_vec3("pointLights[" + str_i + "].pos", light_pos + offset);
    shader->set_float("pointLights[" + str_i + "].kc", light_kc);
    shader->set_float("pointLights[" + str_i + "].kl", light_kl);
    shader->set_float("pointLights[" + str_i + "].kq", light_kq);
}


DirectionalLight::DirectionalLight(const glm::vec3& l_color, const glm::vec3& l_dir)
    : Light(l_color),
      light_dir(l_dir)
{}

void DirectionalLight::to_shader(Shader& shader, const int&, const glm::vec3) const {
    shader.set_vec3("dirLight.lightColor", light_color);
    shader.set_vec3("dirLight.dir", light_dir);
}

void DirectionalLight::to_shader(shared_shader shader, const int&, const glm::vec3) const {
    shader->set_vec3("dirLight.lightColor", light_color);
    shader->set_vec3("dirLight.dir", light_dir);
}
