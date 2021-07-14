#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "window.hh"

/* Glfw, glew and window */
void init_glfw();
void init_glew();
Window init_window(unsigned int width, unsigned int height, const char* title);
