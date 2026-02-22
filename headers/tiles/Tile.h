//
// Created by cadenv07 on 2/22/26.
//

#ifndef NUMERICORE_TILE_H
#define NUMERICORE_TILE_H
#include "graphics/models/Model.h"

class Tile {
public:
    explicit Tile(Model& model): model(std::move(model)) {}

    virtual ~Tile() = default;

    virtual void update() = 0;
    virtual void render(Shader& shader) = 0;

    Model& getModel() { return model; }
protected:
    Model model;
};


#endif //NUMERICORE_TILE_H