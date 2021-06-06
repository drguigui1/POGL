#include <string>
#include <ctime>

#include "init.hh"
#include "render.hh"

int main(int argc, char** argv) {
    std::srand(std::time(nullptr));

    unsigned int width, height;
    if (argc != 3) {
        width = 800;
        height = 600;
    } else {
        width = std::stoi(std::string(argv[1]));
        height = std::stoi(std::string(argv[2]));
    }

    // Init glfw / window / glew
    init_glfw();
    Window window = init_window(width, height, "Title");
    init_glew();

    // Enable z-buffer
    glEnable(GL_DEPTH_TEST);

    // Render loop
    render(window, width, height);

    glfwTerminate();
    return 0;
}
