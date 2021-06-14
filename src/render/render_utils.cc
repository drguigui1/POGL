#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render_utils.hh"
#include "camera.hh"

void render_plane(Shader& shader, const float& ratio, Object& plane) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();
    glm::mat4 model = glm::mat4(1.0f);

    shader.use();
    shader.set_projection_view_model(projection, view, model);
    shader.set_float("iTime", glfwGetTime());

    plane.draw();
}

void render_noised_plane(Shader& shader, const float& ratio, Object& plane) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();
    glm::mat4 model = glm::mat4(1.0f);

    shader.use();
    shader.set_projection_view_model(projection, view, model);
    shader.set_float("height", plane.get_y_max());

    plane.draw();
}

void render_container_cube(Shader& shader, const float& ratio, Object& cube, Texture& texture) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, 0.0f));

    texture.use();
    shader.use();

    shader.set_projection_view_model(projection, view, model);
    shader.set_vec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.set_vec3("lightPos", 0.0f, 5.0f, 0.0f);
    shader.set_vec3("userPos", camera.get_position());

    cube.draw();
}

void render_global_cube(Shader& shader, const float& ratio, Object& cube) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();
    glm::mat4 model = glm::mat4(1.0f);

    shader.use();
    shader.set_projection_view_model(projection, view, model);
    shader.set_float("iTime", glfwGetTime());

    cube.draw();
}

void render_backpack(Shader& shader, const float& ratio, Model& backpack) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();
    glm::mat4 model = glm::mat4(1.0f);

    backpack.draw(shader);

    shader.set_projection_view_model(projection, view, model);

    shader.set_vec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.set_vec3("lightPos", 0.0f, 5.0f, 0.0f);
    shader.set_vec3("userPos", camera.get_position());
}

void render_ball(Shader& shader, const float& ratio, Model& ball) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();
    glm::mat4 model = glm::mat4(1.0f);

    ball.draw(shader);

    shader.set_projection_view_model(projection, view, model);

    shader.set_vec3("pointLight.lightColor", 1.0f, 1.0f, 1.0f);
    shader.set_vec3("pointLight.pos", 1.0f, 20.0f, 0.0f);
    shader.set_float("pointLight.kc", 1.0f);
    shader.set_float("pointLight.kl", 0.09f);
    shader.set_float("pointLight.kq", 0.032f);
    shader.set_vec3("dirLight.lightColor", 1.0f, 1.0f, 1.0f);
    shader.set_vec3("dirLight.dir", -5.0f, -5.0f, -5.0f);
    shader.set_vec3("userPos", camera.get_position());
}

void render_particules(Shader& shader, const float& ratio, Particules& particules, float delta) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();

    shader.use();

    particules.draw(shader, projection, view, 0.15);

    particules.update(delta);
}

void render_skybox(Shader& shader, const float& ratio, Skybox& skybox) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = glm::mat4(glm::mat3(camera.get_matrix_view()));
    glm::mat4 model = glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 50.0f, 50.0f));

    shader.use();

    shader.set_projection_view_model(projection, view, model);
    shader.set_vec3("userPos", camera.get_position());

    skybox.draw();
}