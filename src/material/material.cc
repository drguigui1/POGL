#include "material.hh"

Material::Material(const glm::vec4& a, const glm::vec4& d, const glm::vec4& s)
    : ka(a), kd(d), ks(s)
{}
