//
// Created by cadenv07 on 2/20/26.
//
#define STB_IMAGE_IMPLEMENTATION
#include "graphics/stb_image.h"
#include <GL/glew.h>

#include "graphics/Texture.h"

#include <iostream>
#include <ostream>

Texture::Texture(std::string filename, std::string type)
    : type(std::move(type)), path(std::move(filename))
{
    unsigned int id = 0;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // store with custom deleter so it deletes exactly once
    tex_id = std::shared_ptr<unsigned int>(
        new unsigned int(id),
        [](unsigned int* p) {
            if (p && *p != 0) glDeleteTextures(1, p);
            delete p;
        }
    );

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    GLint fmt = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    if (data) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture: " << path << "\n";
    }

    stbi_image_free(data);
}
