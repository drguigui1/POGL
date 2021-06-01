#ifndef WINDOW_HH_
#define WINDOW_HH_

#include <GLFW/glfw3.h>

class Window {
public:
    Window(unsigned int w, unsigned int h, const char* title);

    /* Methods */
    bool should_close() const;
    bool key_press(int key) const;
    void swap_buffers();

    float get_ratio() const;

    void set_input_mode(int mode, int value);
    void set_close();

    /* Callback */
    void set_framebuffer_size_cb();
    void set_mouse_cb();
    void set_scroll_cb();

private:
    /* Attributes */
    GLFWwindow* window;
    unsigned int width;
    unsigned int height;
};


#endif /* !SRC/WINDOW_HH_ */
