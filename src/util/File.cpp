//
// Created by cadenv07 on 2/20/26.
//

#include "util/File.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

std::string File::readFile() const {
    std::ifstream file(filePath, std::ios::binary);
    if (!file)
        throw std::runtime_error("Failed to open file: " + filePath);

    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
