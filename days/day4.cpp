//
// Created by sonac on 12/4/2021.
//
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>

#include "day4.hpp"
#include "../utils/file.hpp"

struct Line {
    explicit Line(const std::string& input) {
        std::string buf;
        std::stringstream ss(input);
        while (getline(ss, buf, ' ')) {
            if (buf == " " || buf == "")
                continue;
            uncrossed.push_back(std::stoi(buf));
        }
    }
    explicit Line(const std::vector<int>& input) {
        uncrossed = input;
    }
    std::vector<int> uncrossed;
    std::vector<int> crossed;

    void announceNumber(int num) {
        for (int i = 0; i < uncrossed.size(); i++) {
            if (uncrossed[i] == num) {
                crossed.push_back(uncrossed[i]);
                uncrossed.erase(uncrossed.begin() + i);
            }
        }
    }
};

struct Board {
    explicit Board(const std::vector<std::string>& input) {
        for (const std::string& buf: input) {
            Line l = Line(buf);
            lines.push_back(l);
        }
        for (int i = 0; i < 5; i++) {
            std::vector<int> v;
            for (const Line& l: lines) {
                v.push_back(l.uncrossed[i]);
            }
            verticies.emplace_back(v);
        }
    }
    std::vector<Line> verticies;
    std::vector<Line> lines;

    bool won() {
        if (std::any_of(verticies.begin(), verticies.end(),
                        [](const Line& l){return l.uncrossed.empty();}))
            return true;
        if (std::any_of(lines.begin(), lines.end(),
                        [](const Line& l){return l.uncrossed.empty();}))
            return true;
        return false;
    }

    bool announceNumber(int num) {
        for (Line& l: lines)
            l.announceNumber(num);
        for (Line& l: verticies)
            l.announceNumber(num);
        return won();
    }

    int getBoardValue() {
        int res = 0;
        for (const Line& l: lines) {
            for (const int& n: l.uncrossed) {
                res += n;
            }
        }
        return res;
    }
};

void parseNums(const std::string& input, std::vector<int>& nums) {
    std::string buf;
    std::stringstream ss(input);
    while (getline(ss, buf, ',')) {
        nums.push_back(std::stoi(buf));
    }
}

void parseInput(std::vector<int>& nums, std::vector<Board>& boards) {
    File f;
    f.readFile("input/day4_1.txt");
    std::string buf;
    std::stringstream ss(f.getData());
    std::vector<std::string> splitData;
    while (getline(ss, buf, '\n')) {
        splitData.push_back(buf);
    }
    for (int i = 0; i < splitData.size(); i++) {
        if (i == 0) {
            parseNums(splitData[i], nums);
            continue;
        }
        if (i == 1)
            continue;
        if (i % 6 == 0) {
            std::vector<std::string> v(splitData.begin() + (i - 4), 
                    splitData.begin() + (i + 1));
            boards.emplace_back(v);
        }
    }
}

int calcBingo() {
    std::vector<int> nums;
    std::vector<Board> boards;
    parseInput(nums, boards);
    for (const int& n: nums) {
        for (Board& b: boards) {
            if (b.announceNumber(n)) {
                return b.getBoardValue() * n;
            }
        }
    }
    return 0;
}

int calcLooseBingo() {
    std::vector<int> nums;
    std::vector<Board> boards;
    parseInput(nums, boards);
    for (const int& n: nums) {
        for (int i = 0; i < boards.size(); i++) {
            if (boards[i].announceNumber(n)) {
                if (boards.size() == 1)
                    return boards[i].getBoardValue() * n;
                else {
                    boards.erase(boards.begin() + i);
                    i--;
                }
            }
        }
    }
    return 0;
}
