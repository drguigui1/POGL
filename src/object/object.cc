#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>

#include "object.hh"

Object::Object(std::vector<float>& vertices, bool color, bool normal, bool tex)
    : has_EBO(false), y_max(0), y_min(0)
{
    // Compute VAO, VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // VBO init
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    // Determine the nb of float per line
    // 3DCoord + Color + Normal + TextureCoord
    unsigned int size = 3 + (color ? 3 : 0) + (normal ? 3 : 0) + (tex ? 2 : 0);
    nb_vertices = vertices.size() / size;

    // VAO init
    this->init_VAO(size, color, normal, tex);

    // Avoid modification on VAO
    glBindVertexArray(0);
}

Object::Object(std::vector<float>& vertices, std::vector<float>& indices,
        bool color, bool normal, bool tex)
    : has_EBO(true), y_max(0), y_min(0)
{
    // Compute VAO, VBO, EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // VBO init
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    // EBO init
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices), &indices[0], GL_STATIC_DRAW);

    // Determine the nb of float per line
    // 3DCoord + Color + Normal + TextureCoord
    unsigned int size = 3 + (color ? 3 : 0) + (normal ? 3 : 0) + (tex ? 2 : 0);
    nb_vertices = vertices.size() / size;

    // VAO init
    this->init_VAO(size, color, normal, tex);

    // Avoid modification on VAO
    glBindVertexArray(0);
}

Object::~Object() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    if (has_EBO)
        glDeleteBuffers(1, &EBO);
}

void Object::init_VAO(unsigned int size, bool color, bool normal, bool tex) {
    int i = 0;
    int cum_size = 0;

    // position
    add_vertex_attrib(i, 3, size, cum_size);

    // color
    if (color) add_vertex_attrib(i, 3, size, cum_size);

    // normal
    if (normal) add_vertex_attrib(i, 3, size, cum_size);

    // texture coordinates
    if (tex) add_vertex_attrib(i, 2, size, cum_size);
}


void Object::add_vertex_attrib(int& i, int nb, unsigned int size, int& cum_size) {
    // i: the i attribute from the vertices
    // nb: number of float to read for the given attribute
    // size: total size * sizeof(float) per line
    // cum_size: offset of cum_size * sizeof(float)

    glVertexAttribPointer(i, nb, GL_FLOAT, GL_FALSE, size * sizeof(float), (void*) (cum_size*sizeof(float)));
    glEnableVertexAttribArray(i);

    cum_size += nb;
    i += 1;
}

void Object::draw(shared_shader, GLenum type) {
    this->draw(type);
}

void Object::draw(GLenum type) {
    if (this->texture)
        this->texture->use();

    glBindVertexArray(VAO);
    if (this->has_EBO)
        glDrawElements(type, this->nb_vertices, GL_UNSIGNED_INT, 0);
    else
        glDrawArrays(type, 0, this->nb_vertices);
}
