#pragma once

#include "lights.hh"

shared_lights init_lights();
shared_lights init_house_lights();
shared_lights init_trunk_lights();
shared_lights init_museum_lights();
shared_lights init_museum_entrance_lights();
shared_lights init_museum_wall_lights(const glm::vec3& offset);
