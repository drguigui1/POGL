#pragma once

#include <glm/glm.hpp>

enum CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    Camera(glm::vec3 pos=glm::vec3(0.0f, 0.0f, 5.0f),
            glm::vec3 up=glm::vec3(0.0f, 1.0f, 0.0f));

    /* Methods */
    void process_keyboard(CameraMovement direction, float delta);
    void process_mouse_movement(float x, float y);
    void process_mouse_scroll(float y);

    void increase_speed();
    void decrease_speed();

    glm::mat4 get_matrix_view() const;

    /* Getters */
    float get_zoom() const { return zoom; }
    glm::vec3 get_position() const { return position; }

private:
    void update();

    /* Attributes */
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 cup;
    glm::vec3 right;
    glm::vec3 vup;

    float speed;
    float sensitivity;
    float zoom;

    float yaw;
    float pitch;
};

extern Camera camera;
