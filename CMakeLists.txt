cmake_minimum_required(VERSION 3.12)
project(kdzMain)

set(CMAKE_CXX_STANDARD 14)

add_executable(kdzMain main.cpp ReadWriter.h FordFulkerson.h Edge.h EdmondsKarp.h Dinic.h)