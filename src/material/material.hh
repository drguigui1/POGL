#ifndef MATERIAL_HH
#define MATERIAL_HH

#include <glm/glm.hpp>

class Material {

public:
    Material() = default;
    Material(const glm::vec4&, const glm::vec4&, const glm::vec4&);

    /* Getters */
    glm::vec3 get_ka() const { return ka; }
    glm::vec3 get_kd() const { return kd; }
    glm::vec3 get_ks() const { return ks; }

    /* Setters */
    void set_ka(const glm::vec4& v) { ka = v; }
    void set_kd(const glm::vec4& v) { kd = v; }
    void set_ks(const glm::vec4& v) { ks = v; }

private:
    /* Attributes */
    glm::vec3 ka; // ambient
    glm::vec3 kd; // diffuse
    glm::vec3 ks; // specular
};

#endif