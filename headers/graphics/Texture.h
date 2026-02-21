//
// Created by cadenv07 on 2/20/26.
//

#ifndef NUMERICORE_TEXTURE_H
#define NUMERICORE_TEXTURE_H

#include <memory>
#include <string>

class Texture {
public:
    explicit Texture(std::string filename, std::string type = "");
    ~Texture() = default;

    Texture(const Texture&) = default;
    Texture& operator=(const Texture&) = default;
    Texture(Texture&& other) noexcept = default;
    Texture& operator=(Texture&& other) noexcept = default;

    [[nodiscard]] unsigned int getID() const { return tex_id ? *tex_id : 0u; }
    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }
    [[nodiscard]] std::string getType() const { return type; }
    [[nodiscard]] std::string getPath() const { return path; }
private:
    int width{}, height{}, nrChannels{};
    unsigned char *data{};

    std::string type{};
    std::string path{};

    std::shared_ptr<unsigned int> tex_id{};
};


#endif //NUMERICORE_TEXTURE_H