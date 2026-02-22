//
// Created by cadenv07 on 2/21/26.
//

#include "level/Level.h"

#include <GL/glew.h>

#include "tiles/types/BasicTile.h"

Level::Level() {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 20; j++) {
            auto tileModel = Model("res/models/tile/tile.obj",{.TEXTURE_MAG_FILTER = GL_NEAREST});
            auto tile= std::make_unique<BasicTile>(tileModel);
            tile->getModel().translate(glm::vec3(i * 2, j * 2, -5));
            tiles.push_back(std::move(tile));
        }
    }
    auto side = Model("res/models/tile/tile.obj",{.TEXTURE_MIN_FILTER = GL_NEAREST, .TEXTURE_MAG_FILTER = GL_NEAREST, .nineSlice = true, .nineBorderUV = glm::vec4(1/16.0f)});
    auto sideTile = std::make_unique<BasicTile>(side);
    sideTile->getModel().rotate(glm::radians(90.0f), glm::vec3(0, 1, 0));
    sideTile->getModel().translate(glm::vec3(4.f, 19, -1.0f));
    sideTile->getModel().scale(glm::vec3(1.f, 20.f, 1.f));
    tiles.push_back(std::move(sideTile));
}

void Level::render(Shader& shader) const {
    for (auto& tile : tiles) {
        tile->render(shader);
    }
}

void Level::update() {}
