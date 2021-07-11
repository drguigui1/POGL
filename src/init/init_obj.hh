#pragma once

#include <vector>

#include "noise.hh"
#include "object.hh"
#include "particles.hh"

Object create_heightmap_plane(const glm::vec2& center, float width, float height, float step_w, float step_h);
Object create_plane(float dist=15.0f);
Object create_vertical_plane(float dist=15.0f);

Object create_plane2(float center_x, float center_y, int width, int height, float step_w, float step_h, const Noise& noise);
Object create_plane_from_heightmap(const char* path, float center_x, float center_y, float step_w, float step_h);

Object create_cube();

Particles create_snowflake_particles();

Object create_signal_geom();
Object create_plane_geom();
