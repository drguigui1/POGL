#include <GL/glew.h>

#include "texture.hh"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const char* texPath, TextureType t) {
    unsigned char* data;
    int width, height, nb_channels;

    // load the image
    std::cout << "Load texture: " << texPath << '\n';
    data = stbi_load(texPath, &width, &height, &nb_channels, 0);
    if (!data) {
        std::cout << "FAILURE to load the texture: " << texPath << '\n';
        return;
    }

    // create the texture in openGL
    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);

    // set parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // free the loaded image by stbi
    stbi_image_free(data);

    // set the type of the texture
    type = t;
}

Texture::~Texture() {
}

void Texture::use() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->tex_id);
}
