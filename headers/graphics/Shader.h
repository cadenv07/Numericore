//
// Created by cadenv07 on 2/20/26.
//

#ifndef NUMERICORE_SHADER_H
#define NUMERICORE_SHADER_H

#include <string>

class Shader {
public:
    explicit Shader(std::string vertPath, std::string fragPath);
    ~Shader();

    void use() const;

    [[nodiscard]]
    unsigned int getID() const { return s_id; }

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
private:
    unsigned int s_id;
};

#endif //NUMERICORE_SHADER_H