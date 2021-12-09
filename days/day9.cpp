#include <vector>
#include <sstream>
#include <algorithm>

#include "../utils/file.hpp"

struct Map {
    explicit Map(std::string input) {
        std::string buf;
        std::stringstream ss(input);
        while (getline(ss, buf, '\n')) {
            std::vector<int> line;
            for (const char& c: std::vector<char>(buf.begin(), buf.end()))
                line.push_back(int(c) - 48);
            covernMap.push_back(line);
        }
    }
    std::vector<std::vector<int>> covernMap;
    std::vector<std::tuple<int, int>> visited;

    bool isSmallest(int x, int y) {
        int xy = covernMap[x][y];
        if (x != 0 && covernMap[x - 1][y] <= xy)
            return false;
        if (y != 0 && covernMap[x][y - 1] <= xy)
            return false;
        if (x != (covernMap.size() - 1) && covernMap[x + 1][y] <= xy)
            return false;
        if (y != (covernMap.size() - 1) && covernMap[x][y + 1] <= xy)
            return false;
        return true;
    }

    bool isVisited(int x, int y) {
         for (const auto& p: visited)
             if (std::get<0>(p) == x && std::get<1>(p) == y)
                 return true;
         return false;
    }

    int getBasin(int x, int y) {
        visited.emplace_back(x, y);
        int cnt = 1;
        int xy = covernMap[x][y];
        if (x != 0 && covernMap[x - 1][y] > xy && covernMap[x - 1][y] != 9 && !isVisited(x - 1, y))
            cnt += getBasin(x - 1, y);
        if (y != 0 && covernMap[x][y - 1] > xy && covernMap[x][y - 1] != 9 && !isVisited(x, y - 1))
            cnt += getBasin(x, y - 1);
        if (x != (covernMap.size() - 1) && covernMap[x + 1][y] > xy && covernMap[x + 1][y] != 9 && !isVisited(x + 1, y))
            cnt += getBasin(x + 1, y);
        if (y != (covernMap[0].size() - 1) && covernMap[x][y + 1] > xy && covernMap[x][y + 1] != 9 && !isVisited(x, y + 1))
            cnt += getBasin(x, y + 1);
        return cnt;
    };
};

int calcLowetPoints() {
    std::vector<int> lowest;
    File f;
    f.readFile("input/day9_1.txt");
    Map m = Map(f.getData());
    for (int i = 0; i < m.covernMap.size(); i++)
        for (int j = 0; j < m.covernMap[0].size(); j++)
            if (m.isSmallest(i, j))
                lowest.push_back(m.covernMap[i][j]);
    int res = 0;
    for (const int& l: lowest)
        res += (l + 1);
    return res;
}

int64_t calcBasins() {
    std::vector<int> basins;
    File f;
    f.readFile("input/day9_1.txt");
    Map m = Map(f.getData());
    for (int i = 0; i < m.covernMap.size(); i++)
        for (int j = 0; j < m.covernMap[0].size(); j++)
            if (m.isSmallest(i, j)) {
                m.visited.clear();
                basins.push_back(m.getBasin(i, j));
            }
    int64_t res = 1;
    std::sort(basins.begin(), basins.end());
    for (int i = basins.size() - 3; i < basins.size(); i++)
        res *= basins[i];
    return res;
}
