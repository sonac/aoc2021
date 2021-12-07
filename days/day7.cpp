#include <vector>
#include <sstream>
#include <algorithm>
#include <cmath>

#include "../utils/file.hpp"

void getCrabsData(std::vector<int>& inps) {
    File f;
    f.readFile("input/day7_1.txt");
    std::string buf;
    std::stringstream ss(f.getData());
    while (getline(ss, buf, ',')) {
        inps.push_back(std::stoi(buf));
    }
}

int getMedian(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
    int mid = vec.size() / 2;
    return vec[mid];
}

int getAvg(std::vector<int>& vec) {
    float sum = 0.0f;
    for (const int& el: vec)
        sum += el;
    return std::floor(sum / vec.size());
}

int calcAlignFuel() {
    std::vector<int> inps;
    getCrabsData(inps);
    int median = getMedian(inps);
    int res = 0;
    for (const int& i: inps) {
        res += std::abs(i - median);
    }
    return res;
}

int calcAlignIncrFuel() {
    std::vector<int> inps;
    getCrabsData(inps);
    int avg = getAvg(inps);
    int res = 0;
    for (const int& i: inps) {
        int d = std::abs(i - avg);
        res += d * (d + 1) / 2;
    }
    return res;
}

//104822244