#include <iostream>

#include "days/day1.hpp"
#include "days/day2.hpp"
#include "days/day3.hpp"
#include "days/day4.hpp"
#include "days/day5.hpp"
#include "days/day6.hpp"
#include "days/day7.hpp"
#include "days/day8.hpp"
#include "days/day9.hpp"
#include "days/day10.hpp"
#include "days/day11.hpp"
#include "days/day12.hpp"
#include "days/day13.hpp"
#include "days/day14.hpp"
#include "days/day15.hpp"
#include "days/day16.hpp"

int main() {
    std::cout << countInc() << std::endl;
    std::cout << countSliding() << std::endl;
    std::cout << calcDistance() << std::endl;
    std::cout << calcAimedDistance() << std::endl;
    std::cout << calcPower() << std::endl;
    std::cout << calcLifePower() << std::endl;
    std::cout << calcBingo() << std::endl;
    std::cout << calcLooseBingo() << std::endl;
    std::cout << calcOverlappingLines() << std::endl;
    std::cout << calcOverlappingWithDiag() << std::endl;
    std::cout << countLampFish() << std::endl;
    std::cout << countForeverLampFish() << std::endl;
    std::cout << calcAlignFuel() << std::endl;
    std::cout << calcAlignIncrFuel() << std::endl;
    std::cout << countUniqueDigits() << std::endl;
    std::cout << countAllDigits() << std::endl;
    std::cout << calcLowetPoints() << std::endl;
    std::cout << calcBasins() << std::endl;
    std::cout << calcIllegal() << std::endl;
    std::cout << calcClosers() << std::endl;
    std::cout << calcFlashes() << std::endl;
    std::cout << calcAllFlashesStep() << std::endl;
    std::cout << calcPaths() << std::endl;
    //std::cout << calcBiggerPaths() << std::endl; TODO uncomment, it too slow to include in debug
    std::cout << calcVisibleDots() << std::endl;
    printCode();
    std::cout << calcPolymer() << std::endl;
    std::cout << calcBigPolymer() << std::endl;
    std::cout << calcShortestPath() << std::endl;
    //std::cout << calcFullMap() << std::endl; TODO uncoment, also kinda slow
    std::cout << sumVersions() << std::endl;
    std::cout << calcBits() << std::endl;
    return 0;
}
