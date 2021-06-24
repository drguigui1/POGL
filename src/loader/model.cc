#include "model.hh"

#include <iostream>

Model::Model(const std::string& path) {
    Assimp::Importer loader;
    const aiScene* scene = loader.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP:: " << loader.GetErrorString() << '\n';
        return;
    }

    directory = path.substr(0, path.find_last_of('/')) + '/';
    textures_loaded = std::unordered_map<std::string, Texture>();

    load_mesh(scene->mRootNode, scene);
}

static glm::vec3 aiVector3t_to_glmVec3(const aiVector3t<float>& vec) {
    return glm::vec3(vec.x, vec.y, vec.z);
}

static glm::vec2 aiVector3t_to_glmVec2(const aiVector3t<float>& vec) {
    return glm::vec2(vec.x, vec.y);
}

static std::string get_texture_path(const aiMaterial* mat, const std::string& directory, aiTextureType type) {
    aiString str;
    mat->GetTexture(type, 0, &str);

    std::string c_str = str.C_Str();
    if (c_str.empty())
        return "";
    return directory + str.C_Str();
}

std::vector<Texture> Model::load_textures(const aiMaterial* mat) {
    std::vector<Texture> textures;

    // load first diffuse
    std::string str_diffuse = get_texture_path(mat, directory, aiTextureType_DIFFUSE);
    if (!str_diffuse.empty()) {
        if (textures_loaded.find(str_diffuse) == textures_loaded.end())
            textures_loaded[str_diffuse] = Texture(str_diffuse.c_str(), DIFFUSE);

        textures.push_back(textures_loaded[str_diffuse]);
    }

    // load first specular
    std::string str_specular = get_texture_path(mat, directory, aiTextureType_SPECULAR);
    if (!str_specular.empty()) {
        if (textures_loaded.find(str_specular) == textures_loaded.end())
            textures_loaded[str_specular] = Texture(str_specular.c_str(), SPECULAR);
        textures.push_back(textures_loaded[str_specular]);
    }

    // load first specular
    std::string str_normal = get_texture_path(mat, directory, aiTextureType_HEIGHT);
    if (!str_normal.empty()) {
        if (textures_loaded.find(str_normal) == textures_loaded.end())
            textures_loaded[str_normal] = Texture(str_normal.c_str(), NORMAL);
        textures.push_back(textures_loaded[str_normal]);
    }

    return textures;
}

Mesh Model::from_ai_mesh(const aiMesh* ai_mesh, const aiMaterial* material) {
    std::vector<Vertex> vertices;
    for (unsigned int i = 0; i < ai_mesh->mNumVertices; ++i) {
        Vertex vertex;
        vertex.set_position(aiVector3t_to_glmVec3(ai_mesh->mVertices[i]));

        if (ai_mesh->HasNormals())
            vertex.set_normal(aiVector3t_to_glmVec3(ai_mesh->mNormals[i]));

        if (ai_mesh->HasTextureCoords(0))
            vertex.set_tex_coord(aiVector3t_to_glmVec2(ai_mesh->mTextureCoords[0][i]));

        vertices.push_back(vertex);
    }

    std::vector<unsigned int> indices;
    for (unsigned int i = 0; i < ai_mesh->mNumFaces; ++i) {
        for (unsigned int j = 0; j < ai_mesh->mFaces[i].mNumIndices; ++j)
            indices.push_back(ai_mesh->mFaces[i].mIndices[j]);
    }

    // load textures
    std::vector<Texture> textures = load_textures(material);

    return Mesh(vertices, indices, textures);
}

static glm::vec4 aiColor3D_to_glmVec4(const aiColor3D& vec) {
    return glm::vec4(vec.r, vec.g, vec.b, 1.0);
}


static Material load_material(const aiMaterial* material) {
    aiColor3D color;
    material->Get(AI_MATKEY_COLOR_AMBIENT, color);
    auto ka = aiColor3D_to_glmVec4(color);

    material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
    auto kd = aiColor3D_to_glmVec4(color);

    material->Get(AI_MATKEY_COLOR_SPECULAR, color);
    auto ks = aiColor3D_to_glmVec4(color);

    return Material(ka, kd, ks);
}


void Model::load_mesh(aiNode* root, const aiScene* scene) {
    for (unsigned int i = 0; i < root->mNumMeshes; ++i) {
        aiMesh* ai_mesh = scene->mMeshes[root->mMeshes[i]];

        aiMaterial* material = scene->mMaterials[ai_mesh->mMaterialIndex];
        const Mesh mesh = from_ai_mesh(ai_mesh, material);
        meshes.push_back(mesh);

        materials.push_back(load_material(material));
    }

    for(unsigned int i = 0; i < root->mNumChildren; i++)
        load_mesh(root->mChildren[i], scene);
}


void Model::draw(Shader& shader, GLenum) {
    for (unsigned int i = 0; i < meshes.size(); ++i) {
        shader.use();

        const auto material = materials[i];
        shader.set_vec3("ambient", material.get_ka());
        shader.set_vec3("diffuse", material.get_kd());
        shader.set_vec3("specular", material.get_ks());

        meshes[i].draw(shader);
    }
}
