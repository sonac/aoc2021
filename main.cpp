#include <iostream>

#include "utils/file.hpp"

int main() {
    File f;
    f.readFile("input/test.txt");
    std::cout << f.getData();
    return 0;
}
