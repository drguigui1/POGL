#ifndef MODEL_HH
#define MODEL_HH

#include "mesh.hh"

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
    public:
        Model(const std::string& path);

        void draw() const;

    private:
        void load_mesh(aiNode* root, const aiScene* scene);

        std::vector<Mesh> meshes;
};

#endif