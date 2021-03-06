#ifndef MESH_HH
#define MESH_HH

#include <vector>

#include "vertex.hh"
#include "texture.hh"
#include "shader.hh"

class Mesh {
    public:
        Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t);

        void draw(shared_shader shader) const;

    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;
        unsigned int vao;
        unsigned int vbo;
        unsigned int ebo;
};

#endif
