#include "mesh.hh"

#include <GL/glew.h>

Mesh::Mesh(std::vector<Vertex> v, std::vector<unsigned int> i, std::vector<Texture> t) :
    vertices(v),
    indices(i),
    textures(t)
{
    // init VAO
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // init VBO
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    // init EBO
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // bind vertex
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    // bind normal
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));

    // bind texture coord
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (2 * sizeof(glm::vec3)));
}

#include <iostream>

static std::string TextureType_to_string(TextureType type) {
    switch (type) {
    case DIFFUSE:
        return "diffuse";
    case SPECULAR:
        return "specular";
    case NORMAL:
        return "normal";
    case HEIGHT:
        return "height";
    default:
        return "other";
    }
}

void Mesh::draw(Shader& shader) const {
    // activate and bind all textures before drawing
    for (unsigned int i = 0; i < textures.size(); ++i) {
        glActiveTexture(GL_TEXTURE0 + i);

        std::string name = TextureType_to_string(textures[i].get_type());
        //shader.set_int(name + "_map", i + 1);
        glUniform1i(glGetUniformLocation(shader.get_id(), name.c_str()), i);
        glBindTexture(GL_TEXTURE_2D, textures[i].get_id());
    }

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    // set everything back to normal
    glActiveTexture(GL_TEXTURE0);
}
