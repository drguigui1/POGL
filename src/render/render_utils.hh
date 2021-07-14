#pragma once

#include "shader.hh"

#include "particles.hh"
#include "object.hh"
#include "model.hh"
#include "skybox.hh"

// TODO: remove unused functions
// And remove + rename duplicate functions

/* Objects */
void render_plane(Shader& shader, const float& ratio, Object& plane, Texture& texture);
void render_marble_cube(Shader& shader, const float& ratio, Object& cube);
void render_heightmap_plane(Shader& shader, const float& ratio, Object& plane);
void render_terrain(Shader& shader, const float& ratio, Object& terrain);

/* For geometric shader */
void render_signal(Shader& shader, const float& ratio, Object& signal, const float& time);
void render_bubble(Shader& shader, const float& ratio, Object& bubble, const float& time, const unsigned int& width, const unsigned int& height);
void render_grid(Shader& shader, const float& ratio, Object& grid, const float& time, const unsigned int& width, const unsigned int& height);

/* Models */
void render_cuctus(Shader& shader, const float& ratio, Model& cuctus);
