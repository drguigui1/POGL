#pragma once

#include "window.hh"
#include "lights.hh"

/* Glfw, glew and window */
void init_glfw();
void init_glew();
Window init_window(unsigned int width, unsigned int height, const char* title);

/* Lights */
Lights init_lights();
Lights init_house_lights();
