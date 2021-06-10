#ifndef MODEL_HH
#define MODEL_HH

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <unordered_map>

#include "material.hh"
#include "mesh.hh"
#include "shader.hh"

class Model {
    public:
        Model(const std::string& path);

        void draw(Shader& shader) const;

    private:
        void load_mesh(aiNode* root, const aiScene* scene);
        Mesh from_ai_mesh(const aiMesh* ai_mesh, const aiMaterial* material);
        std::vector<Texture> load_textures(const aiMaterial* mat);

        std::vector<Mesh> meshes;
        std::vector<Material> materials;
        std::unordered_map<std::string, Texture> textures_loaded;

        std::string directory;
};

#endif
