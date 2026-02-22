//
// Created by cadenv07 on 2/20/26.
//

#ifndef NUMERICORE_SHADER_H
#define NUMERICORE_SHADER_H

#include <string>
#include <glm/glm.hpp>

class Shader {
public:
    inline static unsigned int s_current;

    explicit Shader(std::string vertPath, std::string fragPath);
    ~Shader();

    void use() const;

    [[nodiscard]]
    unsigned int getID() const { return s_id; }

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, const glm::mat4& m) const;
    void setVec3(const std::string &name, const glm::vec3& v) const;
    void setVec4(const std::string &name, const glm::vec4& v) const;
private:
    mutable std::unordered_map<std::string, int> uniformLocations;
    unsigned int s_id;

    int getUniformLocation(const char *name) const;
};

#endif //NUMERICORE_SHADER_H