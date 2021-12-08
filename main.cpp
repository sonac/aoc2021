#include <iostream>

#include "days/day1.hpp"
#include "days/day2.hpp"
#include "days/day3.hpp"
#include "days/day4.hpp"
#include "days/day5.hpp"
#include "days/day6.hpp"
#include "days/day7.hpp"
#include "days/day8.hpp"

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
    return 0;
}
