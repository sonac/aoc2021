#include <vector>
#include <sstream>
#include <queue>
#include <unordered_map>

#include "../utils/file.hpp"

struct crd {
    explicit crd(int _x, int _y) { x = _x, y = _y; }
    int x;
    int y;

    std::string str() {
        return std::to_string(x) + "," + std::to_string(y);
    }
};

struct Dijkstra {
    explicit Dijkstra(std::string inp) {
        std::string buf;
        std::stringstream ss(inp);
        while (getline(ss, buf, '\n')) {
            std::vector<int> l;
            for (const char& c: buf)
                l.push_back(int(c) - 48);
            mtrx.push_back(l);
        }
    }

    void enchanceMap() {
        std::vector<std::vector<int>> newMtrx;
        for (int i = 0; i < mtrx.size(); i++) {
            std::vector<int> l = mtrx[i];
            std::vector<int> tmp = l;
            for (int j = 0; j < 4; j++) {
                std::vector<int> newTmp = incLine(&tmp);
                l.insert(l.end(), newTmp.begin(), newTmp.end());
                tmp = newTmp;
            }
            newMtrx.push_back(l);
        }
        std::vector<std::vector<int>> newTmpMtrx = newMtrx;
        for (int j = 0; j < 4; j++) {
            std::vector<std::vector<int>> tmpMtrx = newTmpMtrx;
            newTmpMtrx = {};
            for (int i = 0; i < tmpMtrx.size(); i++) {
                std::vector<int> l = incLine(&tmpMtrx[i]);
                newTmpMtrx.push_back(l);
            }
            newMtrx.insert(newMtrx.end(), newTmpMtrx.begin(), newTmpMtrx.end());
        }
        mtrx = newMtrx;
    }

    std::vector<int> incLine(std::vector<int> *line) {
        std::vector<int> nl;
        for (const int& i: *line)
            nl.push_back(inc(i));
        return nl;
    }

    int inc(int i) {
        if (i == 9)
            return 1;
        return i + 1;
    }

    std::vector<crd> getNeighbours(crd c) {
        std::vector<crd> n;
        if (c.x != 0)
            n.push_back(crd(c.x - 1, c.y));
        if (c.x != (mtrx[0].size() - 1))
            n.push_back(crd(c.x + 1, c.y));
        if (c.y != 0)
            n.push_back(crd(c.x, c.y - 1));
        if (c.y != (mtrx.size() - 1))
            n.push_back(crd(c.x, c.y + 1));
        return n;
    }

    int shortestPath() {
        std::queue<crd> unvisited;
        std::unordered_map<std::string, int64_t> dsts;
        for (int i = 0; i < mtrx.size(); i++)
            for (int j = 0; j < mtrx[i].size(); j++) {
                crd c = crd(j, i); 
                unvisited.push(c);
                dsts[c.str()] = INT_MAX;
            }
        crd curNode = unvisited.front();
        dsts[curNode.str()] = 0;
        while (!unvisited.empty()) {
            unvisited.pop();
            if (unvisited.size() == 1)
                int _;
            std::vector<crd> nbs = getNeighbours(curNode);
            for (crd c: nbs) {
                int64_t dst = dsts[curNode.str()] + mtrx[c.y][c.x];
                if (dst < dsts[c.str()]) {
                    dsts[c.str()] = dst;
                    unvisited.push(c);
                }
            }
            curNode = unvisited.front();
        }
        crd lastNode = crd(mtrx[0].size() - 1, mtrx.size() - 1);
        return dsts[lastNode.str()];
    }
    
    std::vector<std::vector<int>> mtrx;
};

int calcShortestPath() {
    File f;
    f.readFile("input/day15_1.txt");

    Dijkstra dj = Dijkstra(f.getData());
    return dj.shortestPath();
}

int calcFullMap() {
    File f;
    f.readFile("input/day15_1.txt");

    Dijkstra dj = Dijkstra(f.getData());
    dj.enchanceMap();
    return dj.shortestPath();
}
