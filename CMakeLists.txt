cmake_minimum_required(VERSION 3.17)
project(circuits)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        circuits
        main.cpp
        Wire.cpp Wire.h
        Point.cpp Point.h
        Circuit.cpp Circuit.h
        CircuitActive.cpp CircuitActive.h
        Matrix.cpp Matrix.h)

add_subdirectory(google_tests)