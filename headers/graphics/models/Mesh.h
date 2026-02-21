//
// Created by cadenv07 on 2/21/26.
//

#ifndef NUMERICORE_MESH_H
#define NUMERICORE_MESH_H

#include <memory>
#include <glm/glm.hpp>

#include "graphics/Texture.h"
#include "graphics/Shader.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    explicit Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    [[nodiscard]] [[maybe_unused]] const std::vector<Vertex>& getVertices() const { return vertices; }
    [[nodiscard]] [[maybe_unused]] const std::vector<unsigned int>& getIndices() const { return indices; }
    [[nodiscard]] [[maybe_unused]] const std::vector<Texture>& getTextures() const { return textures; }

    void draw(const Shader& shader) const;
private:
    unsigned int VAO{}, VBO{}, EBO{};

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    void setupMesh();
};

#endif //NUMERICORE_MESH_H