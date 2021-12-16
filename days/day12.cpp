#include <vector>
#include <sstream>

#include "../utils/file.hpp"

struct node {
    node(std::string v) { val=v; links = {}; };
    std::string val;
    std::vector<node*> links;
};

struct CaveMap {
    explicit CaveMap(std::string inp) {
        std::string buf;
        std::stringstream ss(inp);
        while (getline(ss, buf, '\n')) {
            std::string subBuf;
            std::stringstream sss(buf);
            std::vector<std::string> sNodes;
            while (getline(sss, subBuf, '-')) {
                sNodes.push_back(subBuf);
            }
            node * n1 = new node(sNodes[0]);
            node * n2 = new node(sNodes[1]);
            for (node* n: nodes)
                if (n->val == n1->val)
                    n1 = n;
                else if (n->val == n2->val)
                    n2 = n;
            n1->links.push_back(n2);
            n2->links.push_back(n1);
            if (!containsNode(n1))
                nodes.push_back(n1);
            if (!containsNode(n2))
                nodes.push_back(n2);
        }
    }

    void buildPaths() {
        node * start;
        for (node * n: nodes)
            if (n->val == "start")
                start = n;
        buildPath(*start, "start");

    }

    void buildBiggerPaths() {
        node * start;
        for (node * n: nodes)
            if (n->val == "start")
                start = n;
        buildBiggerPath(*start, "start", false);
    }
//4,5,2
    void buildPath(node& start, std::string curPath) {
        if (start.val == "end") {
            paths.push_back(curPath);
        }
        else {
            for (node *n: start.links) {
                std::string v = n->val;
                if (!isStrUpper(n->val) && pathContains(curPath, v))
                    continue;
                buildPath(*n, curPath + "," + n->val);
            }
        }
    }

    void buildBiggerPath(node& start, std::string curPath, bool twice) {
        if (start.val == "end") {
            paths.push_back(curPath);
        }
        else {
            for (node *n: start.links) {
                std::string v = n->val;
                if (!isStrUpper(n->val) && pathContains(curPath, v) && (twice || (v == "start" || v == "end")))
                    continue;
                else if (!isStrUpper(n->val) && pathContains(curPath, v))
                    buildBiggerPath(*n, curPath + "," + n->val, true);
                else
                    buildBiggerPath(*n, curPath + "," + n->val, twice);
            }
        }
    }

    bool containsNode(node * nn) {
        for (const node* n: nodes)
            if (n->val == nn->val)
                return true;
        return false;
    }

    bool pathContains(std::string p, std::string n) {
        std::string buf;
        std::stringstream ss(p);
        std::vector<std::string> vec;
        while (getline(ss, buf, ','))
            vec.push_back(buf);
        for (const auto pn: vec) {
            if (pn == n)
                return true;
        }
        return false;
    }

    bool isStrUpper(std::string s) {
        for (const char c: s)
            if (!isupper(c))
                return false;
        return true;
    }
    
    std::vector<node*> nodes;
    std::vector<std::string> paths;
};

int calcPaths() {
    File f;
    f.readFile("input/day12_1.txt");

    CaveMap cm = CaveMap(f.getData());
    cm.buildPaths();
    return cm.paths.size();
}

int calcBiggerPaths() {
    File f;
    f.readFile("input/day12_1.txt");

    CaveMap cm = CaveMap(f.getData());
    cm.buildBiggerPaths();
    return cm.paths.size();
}
