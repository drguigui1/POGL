#pragma once

#include <memory>
#include <string>
#include <vector>

#include "object.hh"

class Skybox {
public:
    Skybox(const std::string& directory_path);

    /* Methods */
    void draw();

private:
    /* Methods */
    void load_map(const std::vector<std::string>& faces);

    /* Attributes */
    shared_obj obj;
    unsigned int VAO;
    unsigned int VBO;
    unsigned int nb_vertices;
    unsigned int texture_id;
};

using shared_skybox = std::shared_ptr<Skybox>;
