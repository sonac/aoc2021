#include <vector>
#include <sstream>
#include <unordered_map>

#include "../utils/file.hpp"

struct Polymer {
    explicit Polymer(std::string inp) {
        std::string buf;
        std::stringstream ss(inp);
        std::vector<std::string> tmp;
        while (getline(ss, buf, '\n')) {
            tmp.push_back(buf);
        }
        curElements = tmp[0];
        for (const std::string& rule: std::vector(tmp.begin() + 2, tmp.end())) {
            std::tuple<std::string, char> rl = parseRule(rule);
            rules[std::get<0>(rl)] = std::get<1>(rl);
        }
        polymerToPairs();
    }

    void polymerToPairs() {
        for (int i = 0; i < (curElements.size() - 1); i++)
            pairOcc[std::string(curElements.begin() + i, curElements.begin() + (i + 2))]++;
    }

    void bigInsertPairs() {
        std::unordered_map<std::string, int64_t> newOcc;
        for (const auto p: pairOcc) {
            std::string fPair = std::string() + p.first[0] + rules[p.first];
            std::string sPair = std::string() + rules[p.first] + p.first[1];
            newOcc[fPair] += p.second;
            newOcc[sPair] += p.second;
        }
        pairOcc = newOcc;
    }

    void insertPairs() {
        std::string tmp = curElements;
        int tmpI = 1;
        for (int i = 0; i < (curElements.size() - 1); i++) {
            std::string ss(curElements.begin() + i, curElements.begin() + (i + 2));
            tmp.insert(tmpI, 1, rules[ss]);
            tmpI += 2;
        }
        curElements = tmp;
    }

    int64_t calcPolymer() {
        std::unordered_map<char, int64_t> occ = calcOccurences();
        int64_t max = 0;
        int64_t min = INT64_MAX;
        for (const auto p: occ) {
            if (p.second > max)
                max = p.second;
            if (p.second < min)
                min = p.second;
        }
        return max - min;
    }

    int64_t calcBigPolymer() {
        std::unordered_map<char, int64_t> occ;
        occ[curElements[0]] = 1;
        for (const auto p: pairOcc) {
            occ[p.first[1]] += p.second;
        }
        int64_t max = 0;
        int64_t min = INT64_MAX;
        for (const auto p: occ) {
            if (p.second > max)
                max = p.second;
            if (p.second < min)
                min = p.second;
        }
        return max - min;
    }

    std::unordered_map<char, int64_t> calcOccurences() {
        std::unordered_map<char, int64_t> m;
        for (const char& c: curElements)
            m[c]++;
        return m;
    }

    std::tuple<std::string, char> parseRule(std::string inp) {
        std::string buf;
        std::stringstream ss(inp);
        std::vector<std::string> tmp;
        while (getline(ss, buf, ' ')) {
            tmp.push_back(buf);
        }
        return std::make_tuple(tmp[0], tmp[2][0]);
    }

    std::unordered_map<std::string, char> rules;
    std::unordered_map<std::string, int64_t> pairOcc;
    std::string curElements;
};

int calcPolymer() {
    File f;
    f.readFile("input/day14_1.txt");

    Polymer p = Polymer(f.getData());
    for (int i = 0; i < 10; i++)
        p.insertPairs();
    return p.calcPolymer();
}

int64_t calcBigPolymer() {
    File f;
    f.readFile("input/day14_1.txt");

    Polymer p = Polymer(f.getData());
    for (int i = 0; i < 40; i++)
        p.bigInsertPairs();
    return p.calcBigPolymer();
}