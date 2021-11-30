#include <fstream>
#include <iostream>
#include "file.hpp"

File::File() : data("") {}

File::~File() = default;

void File::readFile(std::string fileName) {
    std::ifstream fileToRead(fileName);
    std::string line; 
    while (getline(fileToRead, line)) {
        data.append(line);
        data.append("\n");
    };
};

std::string File::getData() {
    return data;
}
