#pragma once

#include <memory>

#include "particule.hh"
#include "object.hh"

class Particules {
public:
    Particules(const glm::vec3& cen = glm::vec3(0.0f),
            const glm::vec3& rad_min = glm::vec3(0.0f),
            const glm::vec3& rad_max = glm::vec3(1.0f));

    /* Methods */
    void generate_particules(unsigned int nb);
    void add_particule(const Particule& particule);

    void draw(Shader& shader, const glm::mat4& projection, const glm::mat4& view, float scale=1.0f);
    void update(float delta);

    /* Setters */
    void set_obj(std::shared_ptr<Object> o) { obj = o; }

private:
    /* Methods */
    void add_new_particule(const glm::vec3& offset);

    /* Attributes */
    std::vector<shared_particule> particules;

    glm::vec3 center;
    glm::vec3 radius_min;
    glm::vec3 radius_max;

    // Particule model
    // TODO: a model can be used as an object
    std::shared_ptr<Object> obj;
};
