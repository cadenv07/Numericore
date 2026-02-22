//
// Created by cadenv07 on 2/22/26.
//

#include "tiles/types/BasicTile.h"

void BasicTile::render(Shader& shader) {
    model.draw(shader);
}

void BasicTile::update() {}


