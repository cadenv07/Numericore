//
// Created by cadenv07 on 2/20/26.
//

#ifndef NUMERICORE_TEXTURE_H
#define NUMERICORE_TEXTURE_H

#include <string>

class Texture {
public:
    explicit Texture(std::string filename);
    ~Texture();

    [[nodiscard]] unsigned int getID() const { return tex_id; }
    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }
private:
    int width, height, nrChannels;
    unsigned char *data;

    unsigned int tex_id;
};


#endif //NUMERICORE_TEXTURE_H