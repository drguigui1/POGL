#include "model.hh"

#include <iostream>

Model::Model(const std::string& path) {
    Assimp::Importer loader;
    const aiScene* scene = loader.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << loader.GetErrorString() << '\n';
        return;
    }

    std::cout << scene->mNumMaterials << std::endl;

    load_mesh(scene->mRootNode, scene);
}

static glm::vec3 aiVector3t_to_glmVec3(const aiVector3t<float>& vec) {
    return glm::vec3(vec.x, vec.y, vec.z);
}

static Mesh from_ai_mesh(const aiMesh* ai_mesh) {
    std::vector<Vertex> vertices;
    for (unsigned int i = 0; i < ai_mesh->mNumVertices; ++i) {
        Vertex vertex;
        vertex.set_position(aiVector3t_to_glmVec3(ai_mesh->mVertices[i]));

        if (ai_mesh->HasNormals())
            vertex.set_normal(aiVector3t_to_glmVec3(ai_mesh->mNormals[i]));

        vertices.push_back(vertex);
    }

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < ai_mesh->mNumFaces; ++i) {
        for (unsigned int j = 0; j < ai_mesh->mFaces[i].mNumIndices; ++j)
            indices.push_back(ai_mesh->mFaces[i].mIndices[j]);
    }

    return Mesh(vertices, indices);
}

static glm::vec4 aiColor3D_to_glmVec4(const aiColor3D& vec) {
    return glm::vec4(vec.r, vec.g, vec.b, 1.0);
}

void Model::load_mesh(aiNode* root, const aiScene* scene) {
    for (unsigned int i = 0; i < root->mNumMeshes; ++i) {
        aiMesh* ai_mesh = scene->mMeshes[root->mMeshes[i]];

        aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];
        const Mesh mesh = from_ai_mesh(ai_mesh);
        meshes.push_back(mesh);

        aiColor3D color;
        material->Get(AI_MATKEY_COLOR_AMBIENT, color);
        auto ka = aiColor3D_to_glmVec4(color);

        material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        auto kd = aiColor3D_to_glmVec4(color);

        material->Get(AI_MATKEY_COLOR_SPECULAR, color);
        auto ks = aiColor3D_to_glmVec4(color);

        MaterialTexture mat(ka, kd, ks);
        materials.push_back(mat);
    }

    for(unsigned int i = 0; i < root->mNumChildren; i++)
        load_mesh(root->mChildren[i], scene);
}

void Model::draw(Shader& shader) const {
    for (unsigned int i = 0; i < meshes.size(); ++i) {
        shader.use();

        const auto material = materials[i];
        shader.set_vec3("ambient", material.get_ka());
        shader.set_vec3("diffuse", material.get_kd());
        shader.set_vec3("specular", material.get_ks());

        meshes[i].draw();
    }
}
