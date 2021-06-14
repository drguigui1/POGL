#include <glm/gtc/matrix_transform.hpp>

#include "particules.hh"

#include "random.hh"

Particules::Particules(const glm::vec3& c, const glm::vec3& rad_min, const glm::vec3& rad_max)
    : center(c), radius_min(rad_min), radius_max(rad_max)
{
    std::vector<float> cube_vertices = {
        // position          // colors
        -0.05f, -0.05f, -0.05f, 0.0f, 0.0f, 0.0f,
         0.05f, -0.05f, -0.05f, 1.0f, 0.0f, 0.0f,
         0.05f,  0.05f, -0.05f, 1.0f, 1.0f, 1.0f,
         0.05f,  0.05f, -0.05f, 1.0f, 1.0f, 1.0f,
        -0.05f,  0.05f, -0.05f, 0.0f, 1.0f, 1.0f,
        -0.05f, -0.05f, -0.05f, 0.0f, 0.0f, 0.0f,

        -0.05f, -0.05f,  0.05f, 0.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.05f, 1.0f, 0.0f, 0.0f,
         0.05f,  0.05f,  0.05f, 1.0f, 1.0f, 1.0f,
         0.05f,  0.05f,  0.05f, 1.0f, 1.0f, 1.0f,
        -0.05f,  0.05f,  0.05f, 0.0f, 1.0f, 1.0f,
        -0.05f, -0.05f,  0.05f, 0.0f, 0.0f, 0.0f,

        -0.05f,  0.05f,  0.05f, 1.0f, 0.0f, 0.0f,
        -0.05f,  0.05f, -0.05f, 1.0f, 1.0f, 1.0f,
        -0.05f, -0.05f, -0.05f, 0.0f, 0.0f, 0.0f,
        -0.05f, -0.05f, -0.05f, 0.0f, 0.0f, 0.0f,
        -0.05f, -0.05f,  0.05f, 0.0f, 0.0f, 0.0f,
        -0.05f,  0.05f,  0.05f, 1.0f, 0.0f, 0.0f,

         0.05f,  0.05f,  0.05f, 1.0f, 0.0f, 0.0f,
         0.05f,  0.05f, -0.05f, 1.0f, 1.0f, 1.0f,
         0.05f, -0.05f, -0.05f, 1.0f, 0.0f, 0.0f,
         0.05f, -0.05f, -0.05f, 1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.05f, 0.0f, 0.0f, 0.0f,
         0.05f,  0.05f,  0.05f, 1.0f, 0.0f, 0.0f,

        -0.05f, -0.05f, -0.05f, 0.0f, 0.0f, 0.0f,
         0.05f, -0.05f, -0.05f, 1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.05f, 1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.05f, 1.0f, 0.0f, 0.0f,
        -0.05f, -0.05f,  0.05f, 0.0f, 0.0f, 0.0f,
        -0.05f, -0.05f, -0.05f, 0.0f, 0.0f, 0.0f,

        -0.05f,  0.05f, -0.05f, 0.0f, 1.0f, 1.0f,
         0.05f,  0.05f, -0.05f, 1.0f, 1.0f, 1.0f,
         0.05f,  0.05f,  0.05f, 1.0f, 0.0f, 0.0f,
         0.05f,  0.05f,  0.05f, 1.0f, 0.0f, 0.0f,
        -0.05f,  0.05f,  0.05f, 0.0f, 0.0f, 0.0f,
        -0.05f,  0.05f, -0.05f, 0.0f, 1.0f, 1.0f
    };

    obj = std::make_shared<Object>(cube_vertices, true, false, false);
}

void Particules::draw(Shader& shader, const glm::mat4& projection, const glm::mat4& view, float scale) {
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    for (shared_particule& particule: this->particules) {
        // TODO: Use lifetime or position.y to determine if the obj is still alive
        if (particule->get_lifetime() > 0) {

            glm::mat4 model = glm::translate(glm::mat4(1.0f), particule->get_position());
            model = glm::scale(model, glm::vec3(scale));

            shader.set_mat4("iProjection", projection);
            shader.set_mat4("iView", view);
            shader.set_mat4("iModel", model);

            this->obj->draw(shader);
        }
    }
}

void Particules::add_particule(const Particule& particule) {
    this->particules.push_back(std::make_shared<Particule>(particule));
}

void Particules::add_new_particule(const glm::vec3& offset) {
    Particule particule;
    particule.set_position(this->center + offset);

    this->particules.push_back(std::make_shared<Particule>(particule));
}

void Particules::generate_particules(unsigned int nb_particules) {
    // create this->amount default particle instances
    for (unsigned int i = 0; i < nb_particules; ++i) {
        float x = randm::random_float(this->radius_min.x, this->radius_max.x);
        float y = randm::random_float(this->radius_min.y, this->radius_max.y);
        float z = randm::random_float(this->radius_min.z, this->radius_max.z);
        glm::vec3 offset(x, y, z);
        this->add_new_particule(offset);
    }
}

void Particules::update(float delta) {
    for (shared_particule& particule: this->particules) {
        particule->update(delta);
    }
}
