#include <sstream>
#include <vector>
#include <tuple>
#include <unordered_map>

#include "../utils/file.hpp"

void getData(std::vector<std::string>& lines) {
    File f;
    f.readFile("input/day5_1.txt");
    std::string buf;
    std::stringstream ss(f.getData());
    while (getline(ss, buf, '\n')) {
        lines.push_back(buf);
    };
}

std::tuple<int, int> parseCoords(std::string coords) {
    std::vector<int> tmp;
    std::string buf;
    std::stringstream ss(coords);
    while (getline(ss, buf, ',')) {
        tmp.push_back(std::stoi(buf));
    }
    return std::make_tuple(tmp[0], tmp[1]);
}

bool isDiag(std::tuple<int, int> start, std::tuple<int, int> end) {
    return abs(std::get<0>(start) - std::get<0>(end)) ==
            abs(std::get<1>(start) - std::get<1>(end));
}

std::vector<std::tuple<int, int>> buildHorizontalLine(std::tuple<int, int> start,
        std::tuple<int, int> end) {
    std::vector<std::tuple<int, int>> res;
    for (int i = std::get<0>(start); i <= std::get<0>(end); i++) {
        res.push_back(std::make_tuple(i, std::get<1>(start)));
    }
    return res;
}

std::vector<std::tuple<int, int>> buildVerticalLine(std::tuple<int, int> start,
        std::tuple<int, int> end) {
    std::vector<std::tuple<int, int>> res;
    for (int i = std::get<1>(start); i <= std::get<1>(end); i++) {
        res.push_back(std::make_tuple(std::get<0>(start), i));
    }
    return res;
}

std::vector<std::tuple<int, int>> buildDiagonalLine(std::tuple<int, int> start, 
        std::tuple<int, int> end) {
    std::vector<std::tuple<int, int>> res;
    int xStart = std::get<0>(start);
    int yStart = std::get<1>(start);
    int xEnd = std::get<0>(end);
    int yEnd = std::get<1>(end);
    int x = xStart;
    int y = yStart;
    bool xIncr = true;
    bool yIncr = true;
    if (xStart > xEnd) {
        xIncr = false;
    }
    if (yStart > yEnd) {
        yIncr = false;
    }
    for (int i = 0; i <= abs(xStart - xEnd); i++) {
        res.push_back(std::make_tuple(x, y));
        if (xIncr)
            x++;
        else
            x--;
        if (yIncr)
            y++;
        else
            y--;
    }
    return res;
}

std::vector<std::tuple<int, int>> buildLine(std::string coords) {
    std::vector<std::string> rawPoints;
    std::string buf;
    std::stringstream ss(coords);
    while (getline(ss, buf, ' ')) {
        rawPoints.push_back(buf);
    }
    std::tuple<int, int> start = parseCoords(rawPoints[0]);
    std::tuple<int, int> end = parseCoords(rawPoints[2]);
    std::vector<std::tuple<int, int>> res;
    if (std::get<0>(start) == std::get<0>(end))
        if (std::get<1>(start) < std::get<1>(end))
            res = buildVerticalLine(start, end);
        else
            res = buildVerticalLine(end, start);
    else if (std::get<1>(start) == std::get<1>(end))
        if (std::get<0>(start) < std::get<0>(end))
            res =  buildHorizontalLine(start, end);
        else {
            res = buildHorizontalLine(end, start);
        }
    return res;
}

std::vector<std::tuple<int, int>> buildLineWithDiag(std::string coords) {
    std::vector<std::string> rawPoints;
    std::string buf;
    std::stringstream ss(coords);
    while (getline(ss, buf, ' ')) {
        rawPoints.push_back(buf);
    }
    std::tuple<int, int> start = parseCoords(rawPoints[0]);
    std::tuple<int, int> end = parseCoords(rawPoints[2]);
    std::vector<std::tuple<int, int>> res;
    if (std::get<0>(start) == std::get<0>(end))
        if (std::get<1>(start) < std::get<1>(end))
            res = buildVerticalLine(start, end);
        else
            res = buildVerticalLine(end, start);
    else if (std::get<1>(start) == std::get<1>(end))
        if (std::get<0>(start) < std::get<0>(end))
            res =  buildHorizontalLine(start, end);
        else
            res = buildHorizontalLine(end, start);
    else if (isDiag(start, end))
        res = buildDiagonalLine(start, end);
    return res;
}

bool vectorContainsPoint(std::vector<std::tuple<int, int>> vec, 
        std::tuple<int, int> point) {
    for (const std::tuple<int, int>& p: vec)
        if (std::get<0>(p) == std::get<0>(point) &&
                std::get<1>(p) == std::get<1>(point))
            return true;
    return false;
}

int countMap(const std::unordered_map<std::string, int>& vp) {
    int res = 0;
    for (const auto& pr: vp)
        if (pr.second > 1)
            res++;
    return res;
}

std::string tupleKey(std::tuple<int, int> t) {
    int k1 = std::get<0>(t);
    int k2 = std::get<1>(t);
    return std::to_string(k1) + "," + std::to_string(k2);
}

int calcOverlappingLines() {
    std::vector<std::string> stringLines;
    getData(stringLines);
    std::vector<std::tuple<int, int>> visitedPoints;
    std::vector<std::vector<std::tuple<int, int>>> lines;
    for (const std::string& sl: stringLines)
        lines.push_back(buildLine(sl));
    int res = 0;
    std::unordered_map<std::string, int> vp;
    for (const std::vector<std::tuple<int, int>>& l: lines)
        for (const std::tuple<int, int> p: l) {
            std::string k = tupleKey(p);
            if (vp.find(k) != vp.end())
                vp[k] += 1;
            else
                vp[k] = 1;
        }
    return countMap(vp);
};

uint64_t calcOverlappingWithDiag() {
    std::vector<std::string> stringLines;
    getData(stringLines);
    std::vector<std::tuple<int, int>> visitedPoints;
    std::vector<std::vector<std::tuple<int, int>>> lines;
    for (const std::string& sl: stringLines)
        lines.push_back(buildLineWithDiag(sl));
    std::unordered_map<std::string, int> vp;
    for (const std::vector<std::tuple<int, int>>& l: lines)
        for (const std::tuple<int, int> p: l) {
            std::string k = tupleKey(p);
            if (vp.find(k) != vp.end())
                vp[k] += 1;
            else
                vp[k] = 1;
        }
    return countMap(vp);
}
