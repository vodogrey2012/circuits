cmake_minimum_required(VERSION 3.17)
project(circuits)

set(CMAKE_CXX_STANDARD 14)

add_executable(circuits main.cpp src/Wire.cpp src/Wire.h src/Point.cpp src/Point.h src/Circuit.cpp src/Circuit.h src/CircuitActive.cpp src/CircuitActive.h src/Matrix.h)
#add_executable(tests/TestMatrix.cpp)

add_subdirectory(tests)

#target_link_libraries(
#        ${PROJECT_NAME}
#        gtest
#        gtest_main
#)
