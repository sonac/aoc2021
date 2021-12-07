#include <vector>
#include <sstream>

#include "../utils/file.hpp"

void getFData(std::vector<int>& lines) {
    File f;
    f.readFile("input/day6_1.txt");
    std::string buf;
    std::stringstream ss(f.getData());
    while (getline(ss, buf, ',')) {
        lines.push_back(std::stoi(buf));
    };
}

int countLampFish() {
    std::vector<int> initLF;
    getFData(initLF);
    int d = 0;
    while (d < 80) {
        for (int i = 0; i < initLF.size(); i++) {
            initLF[i]--;
        }
        for (int i = 0; i < initLF.size(); i++) {
            if (initLF[i] == -1) {
                initLF.push_back(8);
                initLF[i] = 6;
            }
        }
        d++;
    }
    return initLF.size();
}

uint64_t countForeverLampFish() {
    std::vector<int> initLF;
    getFData(initLF);
    std::vector<uint64_t> ages(9, 0LL);
    for (const int& age: initLF)
        ages[age]++;
    for (int d = 0; d < 256; d++) {
        uint64_t tmp = ages[0];
        ages[0] = ages[1];
        ages[1] = ages[2];
        ages[2] = ages[3];
        ages[3] = ages[4];
        ages[4] = ages[5];
        ages[5] = ages[6];
        ages[6] = ages[7] + tmp;
        ages[7] = ages[8];
        ages[8] = tmp;
    }
    uint64_t s = 0;
    for (const uint64_t& age: ages)
        s += age;
    return s;
}
