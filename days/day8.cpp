#include <vector>
#include <sstream>
#include <map>
#include <iostream>

#include "../utils/file.hpp"

int compTwo(std::string one, std::string two) {
    int diffs = 0;
    for (const char& c: one)
        if (two.find(c) == std::string::npos)
            diffs++;
    return diffs;
}

bool equal(std::string one, std::string two) {
    return (compTwo(one, two) == 0 && compTwo(two, one) == 0);
}

struct Digits {
    explicit Digits(std::string rawDigs) {
        std::string buf;
        std::stringstream ss(rawDigs);
        std::vector<std::string> line;
        while (getline(ss, buf, '|')) {
            line.push_back(buf);
        }
        for (int i = 0; i < 2; i++) {
            std::stringstream lss(line[i]);
            while (getline(lss, buf, ' ')) {
                if (i == 0)
                    input.push_back(buf);
                else
                    output.push_back(buf);
            }
        }
    }
    std::vector<std::string> input;
    std::vector<std::string> output;
    std::string zero;
    std::string one;
    std::string two;
    std::string three;
    std::string four;
    std::string five;
    std::string six;
    std::string seven;
    std::string eight;
    std::string nine;
    std::map<std::string, int> m;


    void getBases() {
        for (const std::string inp: input) {
            int l = inp.size();
            if (l == 2)
                one = inp;
            else if (l == 3)
                seven = inp;
            else if (l == 4)
                four = inp;
            else if (l == 7)
                eight = inp;
        }
    }

    void getNine() {
        char up;
        std::string n;
        for (const char& c: seven)
            if (four.find(c)  == std::string::npos)
                up = c;
        n = four + up;
        for (const std::string& inp: input)
            if (inp.size() == 6 && compTwo(inp, n) == 1)
                nine = inp;
    }

    void getSixZero() {
        for (const std::string& inp: input)
            if (inp.size() == 6 && inp != nine)
                if (compTwo(one, inp) == 0)
                    zero = inp;
                else { six = inp; }
    }

    void getRest() {
        for (const std::string& inp: input)
            if (inp.size() == 5 && compTwo(six, inp) == 1)
                five = inp;
        for (const std::string& inp: input)
            if (inp.size() == 5 && inp != five)
                if (compTwo(five, inp) == 1)
                    three = inp;
                else {
                    two = inp;
                }
    }

    void buildMap() {
        m[zero] = 0;
        m[one] = 1;
        m[two] = 2;
        m[three] = 3;
        m[four] = 4;
        m[five] = 5;
        m[six] = 6;
        m[seven] = 7;
        m[eight] = 8;
        m[nine] = 9;
    }

    int getDigit(std::string s) {
        for (const auto& p: m)
            if (equal(p.first, s))
                return p.second;
    }

    int getNum(std::vector<int> d) {
        return 1000 * d[0] + 100 * d[1] + 10 * d[2] + d[3];
    }

    int getOutput() {
        std::vector<int> digs;
        if (output.size() != 5)
            std::cout << output[2];
        for (int i = 1; i < 5; i++) {
            int d = getDigit(output[i]);
            digs.push_back(d);
        }
        return getNum(digs);
    }
};

void getAllDigits(std::vector<Digits>& input) {
    File f;
    f.readFile("input/day8_1.txt");
    std::string buf;
    std::stringstream ss(f.getData());
    while (getline(ss, buf, '\n')) {
        Digits digs = Digits(buf);
        input.push_back(digs);
    }
}

int countUniqueDigits() {
    std::vector<Digits> input;
    getAllDigits(input);
    int res = 0;
    for (const Digits& digs: input) {
        for (const std::string& d: digs.output) {
            int l = d.size();
            if (l == 2 || l == 3 || l == 4 || l == 7)
                res++;
        }
    }
    return res;
}

int countAllDigits() {
    std::vector<Digits> input;
    getAllDigits(input);
    int res = 0;
    for (Digits d: input) {
        d.getBases();
        d.getNine();
        d.getSixZero();
        d.getRest();
        d.buildMap();
        res += d.getOutput();
    }
    return res;
}
