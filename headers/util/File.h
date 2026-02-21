//
// Created by cadenv07 on 2/20/26.
//

#ifndef NUMERICORE_FILE_H
#define NUMERICORE_FILE_H

#include <string>

class File {
public:
    explicit File(std::string filePath): filePath(std::move(filePath)) {}

    [[nodiscard]]
    std::string readFile() const;
private:
    std::string filePath;
};

#endif //NUMERICORE_FILE_H