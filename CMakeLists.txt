cmake_minimum_required(VERSION 3.31)
project(CPP_EX1_25_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(CPP_EX1_25_main
        doctest.h
        Graph.cpp
        Graph.h
        main.cpp
        Algorithms.cpp
        Queue.cpp
        Queue.h
        Algorithms.h
        PriorityQueue.h
        PriorityQueue.cpp
        UnionFind.h
        UnionFind.cpp
)
