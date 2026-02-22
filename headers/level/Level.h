//
// Created by cadenv07 on 2/21/26.
//

#ifndef NUMERICORE_LEVEL_H
#define NUMERICORE_LEVEL_H
#include <vector>
#include "tiles/Tile.h"


class Level {
public:
    Level();
    ~Level() = default;

    void update();
    void render(Shader& shader) const;
private:
    std::vector<std::unique_ptr<Tile>> tiles;
};


#endif //NUMERICORE_LEVEL_H