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

    glm::mat4 get_matrix_view();

    /* Setters */
    void set_speed(float v) { speed = v; }
    void set_sensitivity(float v) { sensitivity = v; }
    void set_zoom(float v) { zoom = v; }
    void set_yaw(float v) { yaw = v; }
    void set_pitch(float v) { pitch = v; }

    /* Getters */
    float get_speed() const { return speed; }
    float get_sensitivity() const { return sensitivity; }
    float get_zoom() const { return zoom; }
    float get_yaw() const { return yaw; }
    float get_pitch() const { return pitch; }
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
