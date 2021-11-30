#include <string>

struct File {
    File();
    ~File();
    void readFile(std::string fileName);
    std::string getData();
private:
    std::string data;
};
