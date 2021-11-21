# 'Google_test' is the subproject name
project(tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB ALLSRC
        "../src/*.h"
        "../src/*.cpp"
        )


# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(GTests_run TestMatrix.cpp ${ALLSRC})
target_link_libraries(GTests_run gtest gtest_main)