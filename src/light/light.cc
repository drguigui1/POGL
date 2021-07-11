#include "light.hh"

PointLight::PointLight(const glm::vec3& l_color,
                       const glm::vec3& l_pos,
                       float l_kc,
                       float l_kl,
                       float l_kq)
    : light_color(l_color),
      light_pos(l_pos),
      light_kc(l_kc),
      light_kl(l_kl),
      light_kq(l_kq)
{}

DirectionalLight::DirectionalLight(const glm::vec3& l_color, const glm::vec3& l_dir) :
    light_color(l_color),
    light_dir(l_dir)
{}
