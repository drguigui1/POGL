#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "render_utils.hh"
#include "camera.hh"

void render_plane(Shader& shader, const float& ratio, Object& plane, Texture& texture) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();
    glm::mat4 model = glm::mat4(1.0f);

    texture.use();
    shader.use();

    shader.set_projection_view_model(projection, view, model);
    shader.set_vec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader.set_vec3("lightPos", 0.0f, 5.0f, 0.0f);
    shader.set_vec3("userPos", camera.get_position());

    plane.draw();
}

void render_terrain(shared_shader shader, const float& ratio, Object& terrain) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();
    glm::mat4 model = glm::mat4(1.0f);

    shader->use();

    shader->set_projection_view_model(projection, view, model);
    shader->set_float("amplitude", 5);

    terrain.draw();
}

void render_signal(Shader& shader, const float& ratio, Object& signal, const float& time) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();
    glm::mat4 model = glm::scale(glm::mat4(1), glm::vec3(0.3f, 0.3f, 0.3f));

    shader.use();

    shader.set_mat4("model", model);
    shader.set_mat4("projection", projection);
    shader.set_mat4("view", view);
    shader.set_float("vTime", time);

    signal.draw(GL_POINTS);
}

void render_bubble(Shader& shader, const float& ratio, Object& bubble, const float& time, const unsigned int& width, const unsigned int& height) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();
    glm::mat4 model = glm::scale(glm::mat4(1), glm::vec3(0.3f, 0.3f, 0.3f));

    shader.use();

    shader.set_mat4("model", model);
    shader.set_mat4("projection", projection);
    shader.set_mat4("view", view);
    shader.set_float("vTime", time);
    shader.set_float("vWidth", width);
    shader.set_float("vHeight", height);

    bubble.draw(GL_POINTS);
}

void render_grid(Shader& shader, const float& ratio, Object& grid, const float& time, const unsigned int& width, const unsigned int& height) {
    glm::mat4 projection = glm::perspective(glm::radians(camera.get_zoom()), ratio, 0.1f, 100.0f);
    glm::mat4 view = camera.get_matrix_view();
    glm::mat4 model = glm::scale(glm::mat4(1), glm::vec3(0.3f, 0.3f, 0.3f));

    shader.use();

    shader.set_mat4("model", model);
    shader.set_mat4("projection", projection);
    shader.set_mat4("view", view);
    shader.set_float("vTime", time);
    shader.set_float("vWidth", width);
    shader.set_float("vHeight", height);

    grid.draw(GL_POINTS);
}
