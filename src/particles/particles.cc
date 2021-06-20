#include <glm/gtc/matrix_transform.hpp>

#include "particles.hh"

#include "random.hh"
#include "camera.hh"

Particles::Particles()
    : center(glm::vec3(0.0f)),
    radius_min(glm::vec3(0.0f)),
    radius_max(glm::vec3(1.0f)),
    velocity_min(glm::vec3(0.0f, 0.5f, 0.0f)),
    velocity_max(glm::vec3(0.0f, 0.5f, 0.0f)),
    rotation({})
{}

Particles::Particles(const glm::vec3& c, const glm::vec3& rad_min, const glm::vec3& rad_max)
    : center(c),
    radius_min(rad_min),
    radius_max(rad_max),
    velocity_min(glm::vec3(0.0f, 0.5f, 0.0f)),
    velocity_max(glm::vec3(0.0f, 0.5f, 0.0f)),
    rotation({})
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

void Particles::generate_particles(unsigned int nb_particles) {
    // Create random particles with random y position
    for (unsigned int i = 0; i < nb_particles; ++i) {
        float y = randm::random_float(this->radius_min.y, this->radius_max.y);
        this->particles.push_back(this->create_particle(y));
    }
}

void Particles::add_particle(const Particle& particle) {
    this->particles.push_back(std::make_shared<Particle>(particle));
}

void Particles::draw(Shader& shader, const glm::mat4& projection, const glm::mat4& view) {
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    for (unsigned int i = 0; i < this->particles.size(); ++i) {
        shared_particle particle = this->particles[i];

        // TODO: Use lifetime or position.y to determine if the obj is still alive
        // FIXME: condition on position.y depends on the plane
        if (particle->get_lifetime() > 0 && particle->get_position().y > -0.5) {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), particle->get_position());
            model = glm::scale(model, glm::vec3(particle->get_scale()));
            if (particle->get_rotation().has_value()) {
                model = glm::rotate(model,
                        particle->get_rotation().value().first,
                        particle->get_rotation().value().second);
            }

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
            this->set_new_particle_at(i);
        }
    }
}

void Particles::update(float delta) {
    for (shared_particle& particle: this->particles)
        particle->update(delta);
}

shared_particle Particles::create_particle(float y) const {
    Particle particle;

    // Position
    float x = randm::random_float(this->radius_min.x, this->radius_max.x);
    float z = randm::random_float(this->radius_min.z, this->radius_max.z);
    glm::vec3 offset(x * get_random_sign(), y * get_random_sign(), z * get_random_sign());
    particle.set_position(this->center + offset);

    // Velocity
    x = randm::random_float(this->velocity_min.x, this->velocity_max.x);
    y = randm::random_float(this->velocity_min.y, this->velocity_max.y);
    z = randm::random_float(this->velocity_min.z, this->velocity_max.z);
    particle.set_velocity(glm::vec3(x, y, z));

    // Rotation
    if (this->rotation.has_value()) {
        float radians = this->rotation.value().first + randm::random_float(-10.0f, 10.0f);
        glm::vec3 axis = this->rotation.value().second + randm::random_vec3(-0.5f, 0.5f);
        particle.set_rotation(radians, axis);
    }

    // Scale
    particle.set_scale(randm::random_float(this->scale_min, this->scale_max));

    return std::make_shared<Particle>(particle);
}

void Particles::set_new_particle_at(unsigned int& idx) {
    // Create random particles with y on the top
    float y = this->radius_max.y + randm::random_float(0.0f, 0.5f);
    this->particles[idx] = this->create_particle(y);
}
