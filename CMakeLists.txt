cmake_minimum_required(VERSION 3.21)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 14)

add_executable(Minesweeper main.cpp functions.cpp functions.h map.cpp map.h settings.h)
target_link_libraries(Minesweeper sfml-graphics sfml-audio)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
