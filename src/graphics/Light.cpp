//
// Created by cadenv07 on 2/21/26.
//

#include "graphics/Light.h"

void Light::apply(const Shader &shader) const {
    shader.setVec3("lights[" + std::to_string(id) + "].position", config.position);
    shader.setVec3("lights[" + std::to_string(id) + "].direction", config.direction);
    shader.setVec3("lights[" + std::to_string(id) + "].ambient", config.ambient);
    shader.setVec3("lights[" + std::to_string(id) + "].diffuse", config.diffuse);
    shader.setVec3("lights[" + std::to_string(id) + "].specular", config.specular);
    shader.setVec3("lights[" + std::to_string(id) + "].color", config.color);
    shader.setFloat("lights[" + std::to_string(id) + "].cutOff",  config.cutOff);
    shader.setFloat("lights[" + std::to_string(id) + "].outerCutoff",  config.outerCutoff);
    shader.setFloat("lights[" + std::to_string(id) + "].constant",  config.constant);
    shader.setFloat("lights[" + std::to_string(id) + "].linear",    config.linear);
    shader.setFloat("lights[" + std::to_string(id) + "].quadratic", config.quadratic);
    shader.setInt("lights[" + std::to_string(id) + "].type", config.type);
}