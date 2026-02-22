//
// Created by cadenv07 on 2/20/26.
//

#ifndef NUMERICORE_TEXTURE_H
#define NUMERICORE_TEXTURE_H

#include <memory>
#include <string>

#include <glm/vec4.hpp>

class Texture {
public:
    struct TextConf {
        int TEXTURE_WRAP_S = 0x2901;
        int TEXTURE_WRAP_T = 0x2901;
        int TEXTURE_WRAP_R = 0x2901;
        int TEXTURE_MIN_FILTER = 0x2703;
        int TEXTURE_MAG_FILTER = 0x2601;
        int FLIP_VERTICALLY = 1;
        bool nineSlice = false;
        glm::vec4 nineBorderUV = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
    };

    explicit Texture(std::string filename, const TextConf& cfg, std::string type = "");
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

    TextConf config;

    std::string type{};
    std::string path{};

    std::shared_ptr<unsigned int> tex_id{};
};


#endif //NUMERICORE_TEXTURE_H