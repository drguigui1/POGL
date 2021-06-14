#pragma once

#include "shader.hh"

#include "particules.hh"
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

/* Models */
void render_backpack(Shader& shader, const float& ratio, Model& backpack);
void render_ball(Shader& shader, const float& ratio, Model& ball);

/* Particules */
void render_particules(Shader& shader, const float& ratio, Particules& particules, float delta);

/* Skybox */
void render_skybox(Shader& shader, const float& ratio, Skybox& skybox);
