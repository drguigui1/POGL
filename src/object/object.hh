#ifndef OBJECT_HH_
#define OBJECT_HH_

#include <GL/glew.h>
#include <string>
#include <vector>

class Object {
public:
    Object(std::vector<float>& vertices, bool color, bool normal, bool tex);
    Object(std::vector<float>& vertices, std::vector<float>& indices,
        bool color, bool normal, bool tex);

    ~Object();

    /* Methods */
    void draw(GLenum type=GL_TRIANGLES);

private:
    /* Methods */
    void init_VAO(unsigned int size, bool color, bool normal, bool tex);
    void add_vertex_attrib(int& i, int nb, unsigned int size, int& cum_size);

    /* Attributes */
    std::string id;
    unsigned int nb_vertices;

    // texture
    unsigned char* tex_data;
    int tex_width;
    int tex_height;
    unsigned int tex_id;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    bool has_EBO;
};

#endif /* !SRC/OBJECTS/OBJECT_HH_ */
