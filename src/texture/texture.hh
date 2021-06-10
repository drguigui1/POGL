#ifndef TEXTURE_HH
#define TEXTURE_HH

#include <iostream>

enum TextureType {
    DIFFUSE,
    SPECULAR,
    NORMAL,
    HEIGHT,
    OTHER
};

class Texture {
public:
    Texture(const char* texPath, TextureType t = OTHER);
    ~Texture();

    // use the texture for the object rendering
    void use();
private:
    unsigned int tex_id;
    TextureType type;
};

#endif /* !SRC/TEXTURE/TEXTURE_HH_ */