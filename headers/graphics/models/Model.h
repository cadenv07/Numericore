//
// Created by cadenv07 on 2/21/26.
//

#ifndef NUMERICORE_MODEL_H
#define NUMERICORE_MODEL_H

#include <glm/glm.hpp>

#include <assimp/scene.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "Mesh.h"
#include "graphics/Shader.h"

class Model {
public:
    explicit Model(const char* path) {
        loadModel(path);
    }
    void draw(const Shader& shader) const;

    void translate(const glm::vec3 translation) { model = glm::translate(model, translation); }
    void scale(const glm::vec3 scale) { model = glm::scale(model, scale); }
    void rotate(const float angle, const glm::vec3 axis) { model = glm::rotate(model, angle, axis); }

    [[nodiscard]] const std::vector<Texture>& getTextures() const { return textures_loaded; }
    [[nodiscard]] const glm::mat4& getModelMatrix() const { return model; }
    [[nodiscard]] const std::vector<Mesh>& getMeshes() const { return meshes; }
    [[nodiscard]] const std::string& getDirectory() const { return directory; }
    [[nodiscard]] glm::vec3 getPosition() const { return model[3]; }
    [[nodiscard]] glm::vec3 getScale() const { return glm::vec3(glm::length(glm::vec3(model[0]))); }
    [[nodiscard]] glm::vec3 getRotation() const { return glm::eulerAngles(glm::quat_cast(model)); }
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