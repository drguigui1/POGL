#pragma once

#include "shader.hh"

#include "particles.hh"
#include "object.hh"
#include "model.hh"
#include "skybox.hh"

/* Plane / Terrain */
void render_plane(Shader& shader, const float& ratio, Object& plane, Texture& texture);
void render_vertical_plane(Shader& shader, const float& ratio, Object& plane, const float& time);
void render_terrain(shared_shader shader, const float& ratio, Object& terrain);

/* For geometric shader */
void render_signal(Shader& shader, const float& ratio, Object& signal, const float& time);
void render_bubble(Shader& shader, const float& ratio, Object& bubble, const float& time, const unsigned int& width, const unsigned int& height);
void render_grid(Shader& shader, const float& ratio, Object& grid, const float& time, const unsigned int& width, const unsigned int& height);
