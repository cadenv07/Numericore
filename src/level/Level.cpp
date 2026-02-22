//
// Created by cadenv07 on 2/21/26.
//

#include "level/Level.h"

#include <GL/glew.h>

#include "tiles/types/BasicTile.h"

Level::Level() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            auto tileModel = Model("res/models/tile/tile.obj",{.TEXTURE_MAG_FILTER = GL_NEAREST});
            auto tile= std::make_unique<BasicTile>(tileModel);
            tile->getModel().translate(glm::vec3(i * 2, j * 2, -5));
            tiles.push_back(std::move(tile));
        }
    }
}

void Level::render(Shader& shader) const {
    for (auto& tile : tiles) {
        tile->render(shader);
    }
}

void Level::update() {}
