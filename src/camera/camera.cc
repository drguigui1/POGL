#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "camera.hh"

#include "value.hh"

Camera::Camera(glm::vec3 pos, glm::vec3 up) {
    position = pos;
    vup = up;
    yaw = -90.0f;
    pitch = 0.0f;
    speed = 2.5f;
    sensitivity = 0.1f;
    zoom = 45.0f;
    update();
}

glm::mat4 Camera::get_matrix_view() {
    return glm::lookAt(position, position + front, cup);
}

void Camera::process_keyboard(CameraMovement direction, float delta) {
    switch (direction) {

    case FORWARD:
        this->position += front * speed * delta;
        break;

    case BACKWARD:
        position -= front * speed * delta;
        break;

    case LEFT:
        position -= right * speed * delta;
        break;

    default: // RIGHT
        position += right * speed * delta;
        break;
    }
}

void Camera::process_mouse_movement(float x, float y) {
    yaw = yaw + x * sensitivity;
    pitch = value::clamp(-89.0f, 89.0f, pitch + y * sensitivity);

    update();
}

void Camera::process_mouse_scroll(float y) {
    zoom = value::clamp(1.0, 45.0, zoom - y);
}

void Camera::update() {
    float x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    float y = sin(glm::radians(pitch));
    float z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(glm::vec3(x, y, z));

    right = glm::normalize(glm::cross(front, vup));
    cup = glm::normalize(glm::cross(right, front));
}
