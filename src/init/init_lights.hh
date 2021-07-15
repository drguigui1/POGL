#pragma once

#include "lights.hh"

shared_lights init_lights(const glm::vec3 offset = glm::vec3(0.0f));
shared_lights init_house_lights(const glm::vec3 offset = glm::vec3(0.0f));
shared_lights init_trunk_lights(const glm::vec3 offset = glm::vec3(0.0f));
shared_lights init_museum_lights(const glm::vec3 offset = glm::vec3(0.0f));
shared_lights init_museum_entrance_lights(const glm::vec3 offset = glm::vec3(0.0f));
shared_lights init_museum_wall_lights(const glm::vec3& offset);
