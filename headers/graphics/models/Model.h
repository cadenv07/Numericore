//
// Created by cadenv07 on 2/21/26.
//

#ifndef NUMERICORE_MODEL_H
#define NUMERICORE_MODEL_H

#include <glm/glm.hpp>

#include <assimp/scene.h>

#include "Mesh.h"
#include "graphics/Shader.h"

class Model {
public:
    explicit Model(const char* path) {
        loadModel(path);
    }
    void draw(const Shader& shader) const;
private:
    std::vector<Texture> textures_loaded;
    glm::mat4 model = glm::mat4(1.0f);
    std::vector<Mesh> meshes;
    std::string directory;

    void loadModel(const std::string& path);
    void processNode(const aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(const aiMaterial *mat, aiTextureType type, const std::string& typeName);
};

#endif //NUMERICORE_MODEL_H