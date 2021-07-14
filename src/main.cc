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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Default render with all scenes
    //render(window);

    // Render forest scene
    //render_forest(window);

    // Render museum scene
    render_museum(window);

    // Render scene with rain and snow
    //render_rain_snow(window);

    glfwTerminate();
    return 0;
}
