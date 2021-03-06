#include "particles.hh"

#include "random.hh"
#include "camera.hh"

Particles::Particles(shared_obj o)
    : obj(o),
    position_min(glm::vec3(-1.0f, 0.0f, -1.0f)),
    position_max(glm::vec3( 1.0f, 1.0f,  1.0f)),
    velocity_min(glm::vec3(0.0f, 0.5f, 0.0f)),
    velocity_max(glm::vec3(0.0f, 0.5f, 0.0f)),
    scale_min(0.5f),
    scale_max(1.0f),
    rotation({})
{}

void Particles::generate_particles(const unsigned int& nb_particles) {
    // Create random particles with random y position
    for (unsigned int i = 0; i < nb_particles; ++i) {
        float y = randm::random_float(this->position_min.y, this->position_max.y);
        this->particles.push_back(this->create_particle(y));
    }
}

void Particles::add_particle(const Particle& particle) {
    this->particles.push_back(std::make_shared<Particle>(particle));
}

void Particles::draw(shared_shader shader, shared_lights lights, const glm::mat4& projection, const glm::mat4& view, const glm::vec3& cam_pos) {
    for (unsigned int i = 0; i < this->particles.size(); ++i) {
        const shared_particle particle = this->particles[i];

        if (particle->is_alive(this->position_min, this->position_max)) {
            glm::mat4 model = particle->get_model();

            shader->set_projection_view_model(projection, view, model);
            lights->send_data_to_shader(shader, cam_pos);

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
    float x = randm::random_float(this->position_min.x, this->position_max.x);
    float z = randm::random_float(this->position_min.z, this->position_max.z);
    particle.set_position(glm::vec3(x, y, z));

    // Velocity
    x = randm::random_float(this->velocity_min.x, this->velocity_max.x);
    y = randm::random_float(this->velocity_min.y, this->velocity_max.y);
    z = randm::random_float(this->velocity_min.z, this->velocity_max.z);
    particle.set_velocity(glm::vec3(x, y, z));

    // Rotation
    if (this->rotation.has_value()) {
        float radians = this->rotation.value().first + randm::random_float(-10.0f, 10.0f);
        glm::vec3 axis = this->rotation.value().second + randm::random_vec3(-0.5f, 0.5f);
        particle.set_rotation(std::make_pair(radians, axis));
    }

    // Scale
    particle.set_scale(randm::random_float(this->scale_min, this->scale_max));

    return std::make_shared<Particle>(particle);
}

void Particles::set_new_particle_at(unsigned int& idx) {
    // Create random particles with y on the top
    float y = this->position_max.y + randm::random_float(0.0f, 0.5f);
    this->particles[idx] = this->create_particle(y);
}
