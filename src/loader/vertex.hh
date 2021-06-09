#ifndef VERTEX_HH
#define VERTEX_HH

#include <glm/glm.hpp>

class Vertex {
    public:
        Vertex() = default;

        // setter / getter
        void set_position(glm::vec3 pos) { position = pos; }
        void set_normal(glm::vec3 norm) { normal = norm; }
        void set_tex_coord(glm::vec2 tex_coord) { texture_coord = tex_coord; }

        glm::vec3 get_position() const { return position; }
        glm::vec3 get_normal() const { return normal; }
        glm::vec2 get_texture_coord() const { return texture_coord; }

    private:
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texture_coord;
};

#endif