#ifndef MESH_HH
#define MESH_HH

#include <vector>

#include "vertex.hh"

class Mesh {
    public:
        Mesh(std::vector<Vertex> v, std::vector<unsigned int> i);

        void draw() const;
    private:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        unsigned int vao;
        unsigned int vbo;
        unsigned int ebo;
};

#endif