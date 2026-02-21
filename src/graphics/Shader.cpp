//
// Created by cadenv07 on 2/20/26.
//

#include "graphics/Shader.h"
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "util/File.h"

Shader::Shader(std::string vertPath, std::string fragPath) {
    const File vertFile(std::move(vertPath));
    const File fragFile(std::move(fragPath));

    const std::string vertCode = vertFile.readFile();
    const std::string fragCode = fragFile.readFile();

    const char* vertSource = vertCode.c_str();
    const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertSource, nullptr);
    glCompileShader(vertexShader);

    const char* fragSource = fragCode.c_str();
    const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragSource, nullptr);
    glCompileShader(fragmentShader);

    s_id = glCreateProgram();
    glAttachShader(s_id, vertexShader);
    glAttachShader(s_id, fragmentShader);
    glLinkProgram(s_id);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(s_id);
}

void Shader::use() const {
    glUseProgram(s_id);
}

void Shader::setBool(const std::string &name, const bool value) const {
    glUniform1i(glGetUniformLocation(s_id, name.c_str()), value);
}
void Shader::setInt(const std::string &name, const int value) const {
    glUniform1i(glGetUniformLocation(s_id, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, const float value) const {
    glUniform1f(glGetUniformLocation(s_id, name.c_str()), value);
}
void Shader::setMat4(const std::string &name, const glm::mat4 &m) const {
    glUniformMatrix4fv(glGetUniformLocation(s_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(m));
}