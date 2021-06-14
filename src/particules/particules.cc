#include <glm/gtc/matrix_transform.hpp>

#include "particules.hh"

#include "random.hh"
#include "camera.hh"

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

static float get_random_sign() {
    return randm::random_bool() ? 1 : -1;
}

void Particules::draw(Shader& shader, const glm::mat4& projection, const glm::mat4& view, float scale) {
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    for (unsigned int i = 0; i < this->particules.size(); ++i) {
        shared_particule particule = this->particules[i];

        // TODO: Use lifetime or position.y to determine if the obj is still alive
        // FIXME: condition on position.y depends on the plane
        if (particule->get_lifetime() > 0 && particule->get_position().y > -0.5) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), particule->get_position());
            model = glm::scale(model, glm::vec3(scale));

            shader.set_mat4("projection", projection);
            shader.set_mat4("view", view);
            shader.set_mat4("model", model);

            // FIXME: depends on the shader
            // point light 1
            shader.set_vec3("pointLights[0].lightColor", 1.0f, 1.0f, 1.0f);
            shader.set_vec3("pointLights[0].pos", 3.0f, 3.0f, 0.0f);
            shader.set_float("pointLights[0].kc", 1.0f);
            shader.set_float("pointLights[0].kl", 0.09f);
            shader.set_float("pointLights[0].kq", 0.032f);
            // point light 2
            shader.set_vec3("pointLights[1].lightColor", 1.0f, 1.0f, 1.0f);
            shader.set_vec3("pointLights[1].pos", -3.0f, 3.0f, 0.0f);
            shader.set_float("pointLights[1].kc", 1.0f);
            shader.set_float("pointLights[1].kl", 0.09f);
            shader.set_float("pointLights[1].kq", 0.032f);

            shader.set_vec3("dirLight.lightColor", 1.0f, 1.0f, 1.0f);
            shader.set_vec3("dirLight.dir", -5.0f, -5.0f, -5.0f);
            shader.set_vec3("userPos", camera.get_position());

            shader.set_int("nbLights", 2);

            this->obj->draw(shader);
        } else {
            float x = randm::random_float(this->radius_min.x, this->radius_max.x);
            float y = this->radius_max.y + randm::random_float(0.0f, 0.5f);
            float z = randm::random_float(this->radius_min.z, this->radius_max.z);
            glm::vec3 offset(x * get_random_sign(), y * get_random_sign(), z * get_random_sign());
            this->set_new_particule_at(offset, i);
        }
    }
}

void Particules::add_particule(const Particule& particule) {
    this->particules.push_back(std::make_shared<Particule>(particule));
}

void Particules::set_new_particule_at(const glm::vec3& offset, unsigned int idx) {
    Particule particule;
    particule.set_position(this->center + offset);

    this->particules[idx] = std::make_shared<Particule>(particule);
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
        glm::vec3 offset(x * get_random_sign(), y * get_random_sign(), z * get_random_sign());
        this->add_new_particule(offset);
    }
}

void Particules::update(float delta) {
    for (shared_particule& particule: this->particules) {
        particule->update(delta);
    }
}
