#include <vector>
#include <sstream>
#include <iostream>

#include "../utils/file.hpp"

struct DotPaper {
    explicit DotPaper(std::string inp) {
        std::string buf;
        std::stringstream ss(inp);
        
        while (getline(ss, buf, '\n'))
            if (buf.rfind("fold", 0) == 0)
                foldInstructions.push_back(getFoldInstruction(buf));
            else if(buf == "")
                continue;
            else {
                dotInstructions.push_back(getDotInstruction(buf));
            }
    }

    std::tuple<int, int> getDotInstruction(std::string inp) {
        std::string buf;
        std::stringstream ss(inp);
        std::vector<int> tmp;
        while (getline(ss, buf, ','))
            tmp.push_back(std::stoi(buf));
        return std::make_tuple(tmp[0], tmp[1]);
    }

    std::tuple<int, int> getFoldInstruction(std::string inp) {
        std::string buf;
        std::stringstream ss(inp);
        std::vector<std::string> tmp;
        while (getline(ss, buf, ' '))
            tmp.push_back(buf);
        int f = 0;
        if (tmp[2][0] == 'y')
            f = 1;
        std::string num(tmp[2].begin() + 2, tmp[2].end());
        return std::make_tuple(f, std::stoi(num));
    }

    void fillVec() {
        int maxX = 0;
        int maxY = 0;
        for (const std::tuple<int, int> di: dotInstructions) {
            int x = std::get<0>(di);
            int y = std::get<1>(di);
            if (x > maxX)
                maxX = x;
            if (y > maxY)
                maxY = y;
        }
        std::vector<bool> l(maxX + 1, false);
        std::vector<std::vector<bool>> m(maxY + 1, l);
        paperVec = m;
    }

    void applyDotInstructions() {
        for (const std::tuple<int, int> di: dotInstructions) {
            int x = std::get<0>(di);
            int y = std::get<1>(di);
            paperVec[y][x] = true;
        }
    }

    int visibleDots() {
        int res = 0;
        for (const auto line: paperVec)
            for (const bool b: line)
                if (b)
                    res++;
        return res;
    }

    static void inc(int& i) {
        i++;
    }

    static void dec(int& i) {
        i--;
    }

    std::function<void(int &)> f(bool i) {
        if (i)
            return inc;
        return dec;
    }

    void foldPaper() {
        std::tuple<int, int> fi = foldInstructions[0];
        foldInstructions.erase(foldInstructions.begin(), foldInstructions.begin() + 1);
        int limX = 0;
        int limY = 0;
        if (std::get<0>(fi) == 0) {
            limX = std::get<1>(fi);
            limY = paperVec.size();
        } else {
            limY = std::get<1>(fi);
            limX = paperVec[0].size();
        }
        std::vector<std::vector<bool>> fMatrix;
        for (int y = 0; y < limY; y++) {
            std::vector<bool> line;
            for (int x = 0; x < limX; x++)
                line.push_back(paperVec[y][x]);
            fMatrix.push_back(line);
        }
        int sLimX = 0;
        int sLimY = 0;
        std::function<void(int&)> fnX = f(true);
        std::function<void(int&)> fnY = f(true);
        bool condX = true;
        bool condY = true;
        if (std::get<0>(fi) == 0) {
            sLimX = paperVec[0].size() - 1;
            fnX = f(false);
            condX = false;
        }
        else {
            sLimY = paperVec.size() - 1;
            fnY = f(false);
            condY = false;
        }

        std::vector<std::vector<bool>> sMatrix;
        for (int y = sLimY;;) {
            std::vector<bool> line;
            for (int x = sLimX;;) {
                line.push_back(paperVec[y][x]);
                fnX(x);
                if (condX && x == limX)
                    break;
                if (!condX && x < limX)
                    break;
            }
            sMatrix.push_back(line);
            fnY(y);
            if (condY && y == limY)
                break;
            if (!condY && y < limY)
                break;
        }
        paperVec = fMatrix;
        for (int i = 0; i < fMatrix.size(); i++)
            for (int j = 0; j < fMatrix[i].size(); j++)
                paperVec[i][j] = (fMatrix[i][j] || sMatrix[i][j]);
    }

    void printCode() {
        for (const auto& line: paperVec) {
            for (const bool& c: line) {
                if (c)
                    std::cout << "#";
                else {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }

    std::vector<std::tuple<int, int>> dotInstructions;
    std::vector<std::tuple<int, int>> foldInstructions;
    std::vector<std::vector<bool>> paperVec;
};

int calcVisibleDots() {
    File f;
    f.readFile("input/day13_1.txt");
    DotPaper dp = DotPaper(f.getData());

    dp.fillVec();
    dp.applyDotInstructions();
    dp.foldPaper();

    return dp.visibleDots();
}

void printCode() {
    File f;
    f.readFile("input/day13_1.txt");
    DotPaper dp = DotPaper(f.getData());

    dp.fillVec();
    dp.applyDotInstructions();
    while (dp.foldInstructions.size() != 0)
        dp.foldPaper();
    dp.printCode();
}