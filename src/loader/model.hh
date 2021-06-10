#ifndef MODEL_HH
#define MODEL_HH

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>

#include "material.hh"
#include "mesh.hh"
#include "shader.hh"

class Model {
    public:
        Model(const std::string& path);

        void draw(Shader& shader) const;

    private:
        void load_mesh(aiNode* root, const aiScene* scene);

        std::vector<Mesh> meshes;
        std::vector<Material> materials;
};

#endif
