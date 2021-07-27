#pragma once

#include <vector>

#include "noise.hh"
#include "object.hh"
#include "particles.hh"

Object create_heightmap_plane(const glm::vec2& center, float width, float height, float step_w, float step_h);
Object create_plane(float dist = 15.0f, const float x_center = 0.0f, const float z_factor = 1.0f, const glm::vec3 offset = glm::vec3(0.0f));
Object create_vertical_plane(const float dist = 15.0f);
Object create_vertical_plane(const float& dist_x, const float& dist_y, const glm::vec3& center);

Object create_plane2(float center_x, float center_y, int width, int height, float step_w, float step_h, const Noise& noise);
Object create_plane_from_heightmap(const char* path, float center_x, float center_y, float step_w, float step_h);

Object create_plane_geom();

shared_particles create_particles(const float& nb_particles, shared_obj model, const glm::vec3& pos_min, const glm::vec3& pos_max, const float& scale_min, const float& scale_max, const float rotation = 0.0f);
