#include <iostream>
#include <sstream>
#include <vector>

#include "../utils/file.hpp"

void getData(std::vector<int> &lines) {
   File f;
   f.readFile("input/day1_1.txt");
   std::string buf;
   std::stringstream ss(f.getData());
   while (getline(ss, buf, '\n')) 
   {
      lines.push_back(std::stoi(buf));
   };
}

int countInc() {
   std::vector<int> lines;
   getData(lines);
   int cntr = 0;
   int i = 1;
   while (i < lines.size()) 
   {
      if (lines[i] > lines[i - 1])
         cntr++;
      i++;
   };
   return cntr;
};

int countSliding() {
   std::vector<int> lines;
   getData(lines);
   int curThreeSum = 0;
   int prevThreeSum = lines[0] + lines[1] + lines[2];
   int i = 3;
   int cntr = 0;
   while (i < lines.size()) 
   {
      curThreeSum = lines[i - 2] + lines[i - 1] + lines[i];
      if (curThreeSum > prevThreeSum) 
         cntr++;
      prevThreeSum = curThreeSum;
      i++;
   }
   return cntr;
}
