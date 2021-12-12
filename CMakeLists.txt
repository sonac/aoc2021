cmake_minimum_required(VERSION 3.20)
project(aoc2021)

set(CMAKE_CXX_STANDARD 17)

include_directories(days)
include_directories(utils)

add_executable(aoc2021
        days/day1.cpp
        days/day1.hpp
        days/day2.cpp
        days/day2.hpp
        days/day3.cpp
        days/day3.hpp
        days/day4.cpp
        days/day4.hpp
        days/day5.cpp
        days/day5.hpp
        days/day6.cpp
        days/day6.hpp
        days/day7.cpp
        days/day7.hpp
        days/day8.cpp
        days/day8.hpp
        days/day9.cpp
        days/day9.hpp
        days/day10.cpp
        days/day10.hpp
        days/day11.cpp
        days/day11.hpp
        utils/file.cpp
        utils/file.hpp
        main.cpp days/day4.cpp days/day4.hpp)
