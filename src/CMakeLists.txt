cmake_minimum_required(VERSION 3.14)
project(SuffLineage)

set(CMAKE_CXX_STANDARD 11)

add_executable(SuffLineage main.cpp Load.cpp DNF.cpp Suff.cpp Influ.cpp Change.cpp Change.h)