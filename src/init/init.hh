#ifndef INIT_HH_
#define INIT_HH_

#include "window.hh"
#include "lights.hh"

/* Glfw, glew and window */
void init_glfw();
void init_glew();
Window init_window(unsigned int width, unsigned int height, const char* title);

/* Lights */
Lights init_lights();

#endif /* !INIT_HH_ */
