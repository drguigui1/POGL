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
    Texture() = default;
    Texture(const char* texPath, TextureType t = OTHER);
    ~Texture();

    // use the texture for the object rendering
    void use(int idx = 0) const;

    /* Getters*/
    unsigned int get_id() const { return tex_id; }
    TextureType get_type() const { return type; }

private:
    unsigned int tex_id;
    TextureType type;
};

#endif /* !SRC/TEXTURE/TEXTURE_HH_ */
