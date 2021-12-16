#include <vector>
#include <map>

#include "../utils/file.hpp"

struct Packet {
    virtual ~Packet() = default;
    int version;
    int type;
};

struct LiteralPacket : public Packet {
    explicit LiteralPacket(int _version, int _type, int64_t _value) {
        version = _version;
        type = _type;
        value = _value;
        if (value < 0)
            int _ = 0;
    }
    int64_t value = 0;
};

struct OperatorPacket : public Packet {
    explicit OperatorPacket(int _version, int _type, bool _lenType, int _len) {
        version = _version;
        type = _type;
        lenType = _lenType;
        len = _len;
        subPackets = {};
    }
    bool lenType;
    int len;
    std::vector<Packet*> subPackets;
};

int boolToBit(bool b) {
    if (b)
        return 1;
    return 0;
}

int64_t bitsToDecimal(std::vector<bool> bits) {
    int p = 0;
    int64_t num = 0;
    for (int i = (bits.size() - 1); i >= 0; i--) {
        num += pow(2, p) * boolToBit(bits[i]); 
        p++;
    }
    if (num < 0) {
        int _ = 0;
    }
    return num;
}

Packet* parsePacket(std::vector<bool> *bits) {
    int version = bitsToDecimal(std::vector<bool>(bits->begin(), bits->begin() + 3)); 
    int type = bitsToDecimal(std::vector<bool>(bits->begin() + 3, bits->begin() + 6));
    if (type == 4) {
        int it = 6;
        std::vector<bool> grp = std::vector<bool>(bits->begin() + it, bits->begin() + (it + 5));
        std::vector<bool> lv;
        while (grp[0]) {
            lv.insert(lv.end(), grp.begin() + 1, grp.end());
            it += 5;
            grp = std::vector<bool>(bits->begin() + it, bits->begin() + (it + 5));
        }
        lv.insert(lv.end(), grp.begin() + 1, grp.end());
        int64_t v = bitsToDecimal(lv);
        LiteralPacket* lp = new LiteralPacket(version, type, v);
        it += 5;
        *bits = std::vector<bool>(bits->begin() + it, bits->end());
        return lp;
    }
    bool lenType = (*bits)[6];
    if (lenType) {
        int len = bitsToDecimal(std::vector<bool>(bits->begin() + 7, bits->begin() + 18));
        int i = 0;
        *bits = std::vector<bool>(bits->begin() + 18, bits->end());
        OperatorPacket* op = new OperatorPacket(version, type, lenType, len);
        while (i < len) {
            Packet* p = parsePacket(bits);
            op->subPackets.push_back(p);
            i++;
        }
        return op;
    } else {
        int len = bitsToDecimal(std::vector<bool>(bits->begin() + 7, bits->begin() + 22));
        *bits = std::vector<bool>(bits->begin() + 22, bits->end());
        int initSz = bits->size();
        OperatorPacket* op = new OperatorPacket(version, type, lenType, len);
        while ((initSz - bits->size()) < len) {
            Packet* p = parsePacket(bits);
            op->subPackets.push_back(p);
        }
        return op;
    }
}

int64_t evalPacket(Packet* p) {
    if (p->type == 4) {
        return dynamic_cast<LiteralPacket*>(p)->value;
    }
    OperatorPacket* pct = dynamic_cast<OperatorPacket*>(p);
    if (pct->type == 0) {
        int64_t s = 0;
        for (Packet* sp: pct->subPackets)
            s += evalPacket(sp);
        return s;
    }
    if (pct->type == 1) {
        int64_t pr = 1;
        for (Packet* sp: pct->subPackets)
            pr *= evalPacket(sp);
        return pr;
    }
    if (pct->type == 2) {
        int64_t m = INT_MAX;
        for (Packet* sp: pct->subPackets) {
            int64_t ep = evalPacket(sp);
            if (ep < m)
                m = ep;
        }
        return m;
    }
    if (pct->type == 3) {
        int64_t m = 0;
        for (Packet* sp: pct->subPackets) {
            int64_t ep = evalPacket(sp);
            if (ep > m)
                m = ep;
        }
        return m;
    }
    if (pct->type == 5) {
        int64_t fP = evalPacket(pct->subPackets[0]);
        int64_t sP = evalPacket(pct->subPackets[1]);
        if (fP > sP)
            return 1;
        return 0;
    }
    if (pct->type == 6) {
        int64_t fP = evalPacket(pct->subPackets[0]);
        int64_t sP = evalPacket(pct->subPackets[1]);
        if (fP < sP)
            return 1;
        return 0;
    }
    if (pct->type == 7) {
        int64_t fP = evalPacket(pct->subPackets[0]);
        int64_t sP = evalPacket(pct->subPackets[1]);
        if (fP == sP)
            return 1;
        return 0;
    }
    return 0;
}

std::vector<bool> hexToBits(std::string hexes) {
    std::map<char, std::vector<bool>> m;
    m['0'] = {false, false, false, false};
    m['1'] = {false, false, false, true};
    m['2'] = {false, false, true, false};
    m['3'] = {false, false, true, true};
    m['4'] = {false, true, false, false};
    m['5'] = {false, true, false, true};
    m['6'] = {false, true, true, false};
    m['7'] = {false, true, true, true};
    m['8'] = {true, false, false, false};
    m['9'] = {true, false, false, true};
    m['A'] = {true, false, true, false};
    m['B'] = {true, false, true, true};
    m['C'] = {true, true, false, false};
    m['D'] = {true, true, false, true};
    m['E'] = {true, true, true, false};
    m['F'] = {true, true, true, true};

    std::vector<bool> res;
    for (const char& c: hexes)
        res.insert(res.end(), m[c].begin(), m[c].end());
    return res;
}

int calcVersions(Packet* p) {
    if (p->type == 4)
        return p->version;
    int s = p->version;
    for (Packet* pct: dynamic_cast<OperatorPacket*>(p)->subPackets)
        s += calcVersions(pct);
    return s;
}

bool cont(std::vector<bool> *bits) {
    for (const bool b: *bits)
        if (b)
            return true;
    return false;
}

int sumVersions() {
    File f;
    f.readFile("input/day16_1.txt");

    std::vector<bool> bits = hexToBits(f.getData());
    Packet* packet = parsePacket(&bits);

    int res = calcVersions(packet);

    return res;
}

int64_t calcBits() {
    File f;
    f.readFile("input/day16_1.txt");

    std::vector<bool> bits = hexToBits(f.getData());
    Packet* packet = parsePacket(&bits);

    int64_t res = evalPacket(packet);
    return res;
}
