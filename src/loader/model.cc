#include "model.hh"

#include <iostream>

Model::Model(const std::string& path) {

    std::cout << path << std::endl;
    Assimp::Importer loader;
    const aiScene* scene = loader.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << loader.GetErrorString() << '\n';
        return;
    }

    std::cout << scene->mRootNode->mNumMeshes << std::endl;
    load_mesh(scene->mRootNode, scene);
}

static glm::vec3 aiVector3t_to_glmVec3(aiVector3t<float> vec) {
    return glm::vec3(vec.x, vec.y, vec.z);
}

static Mesh from_ai_mesh(aiMesh* ai_mesh) {
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


void Model::load_mesh(aiNode* root, const aiScene* scene) {
    std::cout << root->mNumMeshes << std::endl;

    for (unsigned int i = 0; i < root->mNumMeshes; ++i) {
        aiMesh* ai_mesh = scene->mMeshes[root->mMeshes[i]];
        Mesh mesh = from_ai_mesh(ai_mesh);
        meshes.push_back(mesh);
    }
}

void Model::draw() const {
    for (const auto& mesh : meshes)
        mesh.draw();
}