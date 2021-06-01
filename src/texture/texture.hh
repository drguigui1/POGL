#ifndef TEXTURE_HH
#define TEXTURE_HH

#include <iostream>

class Texture {
public:
    Texture(const char* texPath);
    ~Texture();

    // use the texture for the object rendering
    void use();
private:
    unsigned int tex_id;
};

#endif /* !SRC/TEXTURE/TEXTURE_HH_ */