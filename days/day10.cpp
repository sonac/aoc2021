#include <vector>
#include <sstream>
#include <stack>
#include <algorithm>

#include "../utils/file.hpp"

void getBracesData(std::vector<std::string>& inp) {
    File f;
    f.readFile("input/day10_1.txt");
    std::string buf;
    std::stringstream ss(f.getData());
    while (getline(ss, buf, '\n')) {
        inp.push_back(buf);
    }
}

int illegalVal(char c) {
    if (c == ')')
        return 3;
    if (c == ']')
        return 57;
    if (c == '}')
        return 1197;
    if (c == '>')
        return 25137;
    return 0;
}

int closingVal(char c) {
    if (c == ')')
        return 1;
    if (c == ']')
        return 2;
    if (c == '}')
        return 3;
    if (c == '>')
        return 4;
    return 0;
}

bool isClosing(char c) {
    return (c == '}' || c == ')' || c == ']' || c == '>');
}

char getClosing(char c) {
    if (c == '(')
        return ')';
    if (c == '{')
        return '}';
    if (c == '[')
        return ']';
    if (c == '<')
        return '>';
    return '!';
}

int getIllegal(std::string s) {
    std::stack<char> ops;
    for (const char c: s)
        if (isClosing(c)) {
            if (ops.empty())
                return illegalVal(c);
            char op = ops.top();
            ops.pop();
            if (getClosing(op) != c)
                return illegalVal(c);
        } else {
            ops.push(c);
        }
    return 0;
}

std::vector<char> getClosers(std::string s) {
    std::stack<char> ops;
    std::vector<char> closers;
    for (const char c: s)
        if (isClosing(c)) {
            if (ops.empty())
                return {};
            char op = ops.top();
            ops.pop();
            if (getClosing(op) != c)
                return {};
        } else {
            ops.push(c);
        }
    while (!ops.empty()) {
        char op = ops.top();
        closers.push_back(getClosing(op));
        ops.pop();
    }
    return closers;
}

int64_t calcCloser(std::vector<char> v) {
    int64_t curTot = 0;
    for (const char c: v)
        curTot = (curTot * 5) + closingVal(c);
    return curTot;
}

int calcIllegal() {
    std::vector<std::string> inp;
    getBracesData(inp);
    std::vector<int> results;
    for (const std::string i: inp)
        results.push_back(getIllegal(i));
    int res = 0;
    for (const int& r: results)
        res += r;
    return res;
}

int64_t calcClosers() {
    std::vector<std::string> inp;
    getBracesData(inp);
    std::vector<std::vector<char>> closers;
    for (const std::string i: inp)
        closers.push_back(getClosers(i));
    std::vector<int64_t> results;
    for (const std::vector<char> cl: closers) {
        if (cl.empty())
            continue;
        results.push_back(calcCloser(cl));
    }
    std::sort(results.begin(), results.end());
    return results[(results.size() / 2)];
}
