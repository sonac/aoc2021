#include <sstream>
#include <vector>

#include "../utils/file.hpp"

struct MovingInput {
    std::string dir;
    int len;
};

MovingInput parseLine(std::string line) {
    std::string buf;
    std::stringstream ss(line);
    std::vector<std::string> tmp;
    MovingInput mi;
    while (ss >> buf) 
    {
        tmp.push_back(buf);
    };
    mi.dir = tmp[0];
    mi.len = std::stoi(tmp[1]);
    return mi;
};

void getData(std::vector<MovingInput> &lines) {
    File f;
    f.readFile("input/day2_1.txt");
    std::string buf;
    std::stringstream ss(f.getData());
    while (getline(ss, buf, '\n'))
    {
        lines.push_back(parseLine(buf)); 
    };
};

int calcDistance() {
    std::vector<MovingInput> lines;
    getData(lines);
    int distance = 0;
    int depth = 0;
    int i = 0;
    while (i < lines.size())
    {
        if (lines[i].dir == "forward")
            distance += lines[i].len;
        if (lines[i].dir == "down")
            depth += lines[i].len;
        if (lines[i].dir == "up")
            depth -= lines[i].len;
        i++;
    };
    return distance * depth;
};

int calcAimedDistance() {
    std::vector<MovingInput> lines;
    getData(lines);
    int distance = 0;
    int depth = 0;
    int aim = 0;
    int i = 0;
    while (i < lines.size())
    {
        int l = lines[i].len;
        std::string d = lines[i].dir;
        if (d == "forward") {
            distance += l;
            depth += (aim * l);
        }
        if (d == "down") {
            aim += l;
        }
        if (d == "up") {
            aim -= l;
        }
        i++;
    };
    return distance * depth;
};
