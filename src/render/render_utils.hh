#pragma once

#include "shader.hh"

#include "particles.hh"
#include "object.hh"
#include "model.hh"
#include "skybox.hh"

// TODO: remove unused functions
// And remove + rename duplicate functions

/* Objects */
void render_plane(Shader& shader, const float& ratio, Object& plane);
void render_noised_plane(Shader& shader, const float& ratio, Object& plane);
void render_container_cube(Shader& shader, const float& ratio, Object& cube, Texture& texture);
void render_global_cube(Shader& shader, const float& ratio, Object& cube);

void render_signal(Shader& shader, const float& ratio, Object& signal, const float& time);

/* Models */
void render_backpack(Shader& shader, const float& ratio, Model& backpack);
void render_ball(Shader& shader, const float& ratio, Model& ball);
void render_cuctus(Shader& shader, const float& ratio, Model& cuctus);

/* Particles */
void render_particles(Shader& shader, const float& ratio, Particles& particles, float delta);

/* Skybox */
void render_skybox(Shader& shader, const float& ratio, Skybox& skybox);
