#include <sstream>
#include <vector>
#include <cmath>

#include "../utils/file.hpp"

void getData(std::vector<std::vector<int>> &lines) {
    File f;
    f.readFile("input/day3_1.txt");
    std::string buf;
    std::stringstream ss(f.getData());
    while (getline(ss, buf, '\n')) {
        std::vector<int> line;
        for (const char& c: buf)
        {
            line.push_back(int(c) - 48);
        }
        lines.push_back(line);
    };
};

int toDecimal(std::vector<int> binary) {
    int p = 0;
    int i = binary.size() - 1;
    int res = 0;
    do {
        int cur = (std::pow(2, p) * binary[i]);
        res += cur;
        i--;
        p++;
    } while (i >= 0);
    return res;
}

int calcPower() {
    std::vector<std::vector<int>> lines;
    getData(lines);
    std::vector<int> sums(lines[0].size(), 0);    
    for (const std::vector<int>& l: lines) {
        for (int i = 0; i < l.size(); i++) {
            sums[i] += l[i];
        }
    }
    std::vector<int> gamma(lines[0].size(), 0);
    std::vector<int> eps(lines[0].size(), 0);
    int threshold = lines.size() / 2;
    for (int i = 0; i < sums.size(); i++) {
        if (sums[i] > threshold) {
            gamma[i] = 1;
            eps[i] = 0;
        } else {
            gamma[i] = 0;
            eps[i] = 1;
        }
    };
    return toDecimal(gamma) * toDecimal(eps);
};

std::vector<std::vector<int>> filterVec(std::vector<std::vector<int>>& lines, bool mostCommon, int pos) {
    int s = 0;
    for (const std::vector<int>& el: lines) {
        s += el[pos];
    }
    int fltr = 0;
    if (mostCommon) {
        if (s >= (float(lines.size()) / 2.0)) {
            fltr = 1;
        }
    } else {
        if (s < (float(lines.size()) / 2.0))
            fltr = 1;
    }
    std::vector<std::vector<int>> res;
    for (const std::vector<int>& el: lines) {
        if (el[pos] == fltr)
            res.push_back(el); 
    }
    return res;
}

int calcLifePower() {
    std::vector<std::vector<int>> lines;
    getData(lines);
    int p = 0;
    std::vector<std::vector<int>> oxy = lines;
    while (p < lines[0].size() && oxy.size() != 1) {
        oxy = filterVec(oxy, true, p);
        p++;
    }
    p = 0;
    std::vector<std::vector<int>> co2 = lines;
    while (p < lines[0].size() && co2.size() != 1) {
        co2 = filterVec(co2, false, p);
        p++;
    }
    return toDecimal(oxy[0]) * toDecimal(co2[0]);
}
