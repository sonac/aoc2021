#include <vector>
#include <sstream>
#include <algorithm>


#include "../utils/file.hpp"

struct OctopusMap {
    explicit OctopusMap(std::string inp) {
        flashes = 0;
        std::string buf;
        std::stringstream ss(inp);

        while (getline(ss, buf, '\n')) {
            std::vector<int> line;
            for (const char& c: std::vector<char>(buf.begin(), buf.end()))
                line.push_back(int(c) - 48);
            data.push_back(line);
        }
    }

    int clamp(int v, int lo, int hi) {
        if (v > hi)
            return hi;
        if (v < lo)
            return lo;
        return v;
    }

    bool hasTens() {
        for (int i = 0; i < data.size(); i++)
            for (int j = 0; j < data[i].size(); j++)
                if (data[i][j] >= 10 && !hasFlashed(i, j))
                    return true;
        return false;
    }

    bool hasFlashed(int x, int y) {
        for (const auto& p: flashed)
            if (std::get<0>(p) == x && std::get<1>(p) == y)
                return true;
        return false;
    }

    std::tuple<int, int> closestTen() {
        for (int i = 0; i < data.size(); i++)
            for (int j = 0; j < data[i].size(); j++)
                if (data[i][j] >= 10 && !hasFlashed(i, j))
                    return std::make_tuple(i, j);
        throw "no ten found";
    }

    void incNeighbours(int x, int y) {
        for (int i = clamp(x - 1, 0, data.size() - 1); i <= clamp(x + 1, 0, data.size() - 1); i++)
            for (int j = clamp(y - 1, 0, data[i].size() - 1); j <= clamp(y + 1, 0, data[i].size() - 1); j++)
                data[i][j]++;
    }

    void performStep() {
        for (int i = 0; i < data.size(); i++)
            for (int j = 0; j < data[i].size(); j++)
                data[i][j]++;
        while (hasTens()) {
            std::tuple<int, int> xy = closestTen();
            const auto& [x, y] = xy;
            incNeighbours(x, y);
            flashed.push_back(std::make_tuple(x, y));
            flashes++;
        }

        for (int i = 0; i < data.size(); i++)
            for (int j = 0; j < data[i].size(); j++)
                if (data[i][j] > 9)
                    data[i][j] = 0;
    }

    int calcFlashes() {
        int i = 0;
        while (i < 100) {
            performStep();
            i++;
            flashed.clear();
        }
        return flashes;
    }

    int calcStep() {
        int i = 0;
        int prevFlashes = 0;
        int diff = flashes - prevFlashes;
        while (diff != 100) {
            prevFlashes = flashes;
            performStep();
            i++;
            flashed.clear();
            diff = flashes - prevFlashes;
        }
        return i;
    }

    std::vector<std::vector<int>> data;
    int flashes;
    std::vector<std::tuple<int, int>> flashed;
};

int calcFlashes() {
    File f;
    f.readFile("input/day11_1.txt");
    OctopusMap om = OctopusMap(f.getData());
    return om.calcFlashes();
}

int calcAllFlashesStep() {
    File f;
    f.readFile("input/day11_1.txt");
    OctopusMap om = OctopusMap(f.getData());
    return om.calcStep();
}