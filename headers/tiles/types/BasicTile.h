//
// Created by cadenv07 on 2/22/26.
//

#ifndef NUMERICORE_BASICTILE_H
#define NUMERICORE_BASICTILE_H
#include "tiles/Tile.h"


class BasicTile : public Tile {
public:
    explicit BasicTile(Model& model): Tile(model) {}

    void render(Shader& shader) override;
    void update() override;
};


#endif //NUMERICORE_BASICTILE_H