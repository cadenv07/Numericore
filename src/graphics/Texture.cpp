//
// Created by cadenv07 on 2/20/26.
//
#define STB_IMAGE_IMPLEMENTATION
#include "graphics/stb_image.h"
#include <GL/glew.h>

#include "graphics/Texture.h"

#include <iostream>
#include <ostream>

Texture::Texture(std::string filename) {
    const char* charArr = std::move(filename).c_str();

    glGenTextures(1, &tex_id);
    glBindTexture(GL_TEXTURE_2D, tex_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load(charArr, &width, &height, &nrChannels, 0);
    const GLint fmt = (nrChannels == 4) ? GL_RGBA : GL_RGB;
    if (data) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Texture::~Texture() {
    glDeleteTextures(1, &tex_id);
}
