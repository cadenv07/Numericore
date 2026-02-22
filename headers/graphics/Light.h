//
// Created by cadenv07 on 2/21/26.
//

#ifndef NUMERICORE_LIGHT_H
#define NUMERICORE_LIGHT_H
#include <glm/vec3.hpp>

#include "Shader.h"

class Light {
public:
    constexpr static int DIRECTIONAL = 1;
    constexpr static int POINT = 2;
    constexpr static int SPOT = 3;

    inline static int numLights = 0;

    struct LightConfig {
        glm::vec3 position = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::vec3 ambient{0.2f};
        glm::vec3 diffuse{0.5f};
        glm::vec3 specular{1.0f};
        glm::vec3 color{1.0f};
        float cutOff{glm::cos(glm::radians(12.5f))};
        float outerCutoff{glm::cos(glm::radians(17.5f))};

        float constant = 1.0f;
        float linear = 0.09f;
        float quadratic = 0.032f;

        int type = 0;
    };

    explicit Light(int type = DIRECTIONAL): config({.type = type }), id(numLights++) {}
    explicit Light(const LightConfig& cfg): config(cfg), id(numLights++) {}
    ~Light() = default;

    [[nodiscard]] const LightConfig& getConfig() const { return config; }
    [[nodiscard]] int getId() const { return id; }

    void setPosition(const glm::vec3& pos) { config.position = pos; }
    void setDirection(const glm::vec3& dir) { config.direction = dir; }
    void setColor(const glm::vec3& color) { config.color = color; }
    void setCutOff(const float cutOff) { config.cutOff = glm::cos(glm::radians(cutOff)); }
    void setOuterCutOff(const float outerCutOff) { config.outerCutoff = glm::cos(glm::radians(outerCutOff)); }
    void setConstant(const float constant) { config.constant = constant; }
    void setLinear(const float linear) { config.linear = linear; }
    void setQuadratic(const float quadratic) { config.quadratic = quadratic; }
    void setType(const int type) { config.type = type; }

    void setAmbient(const glm::vec3& ambient) { config.ambient = ambient; }
    void setDiffuse(const glm::vec3& diffuse) { config.diffuse = diffuse; }
    void setSpecular(const glm::vec3& specular) { config.specular = specular; }

    void apply(const Shader& shader) const;
private:
    LightConfig config;
    int id = 0;
};

#endif //NUMERICORE_LIGHT_H