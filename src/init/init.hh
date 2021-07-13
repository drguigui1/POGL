#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "window.hh"
#include "renderer.hh"

/* Glfw, glew and window */
void init_glfw();
void init_glew();
Window init_window(unsigned int width, unsigned int height, const char* title);

/* Renderer objects */
RendererObject create_renderer_obj(const char* vertex_path,
        const char* fragment_path, const char* model_path, shared_lights lights,
        const bool& cam, const float& scale, const glm::vec3& translate);
