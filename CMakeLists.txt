cmake_minimum_required(VERSION 3.20)
project(aoc2021)

set(CMAKE_CXX_STANDARD 14)

include_directories(days)
include_directories(utils)

add_executable(aoc2021
        days/day1.cpp
        days/day1.hpp
        days/day2.cpp
        days/day2.hpp
        days/day3.cpp
        days/day3.hpp
        utils/file.cpp
        utils/file.hpp
        main.cpp days/day4.cpp days/day4.hpp)
