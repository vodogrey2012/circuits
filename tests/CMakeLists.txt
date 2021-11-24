# 'Google_test' is the subproject name
project(tests)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

# 'lib' is the folder with Google Test sources
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB ALLSRC
        "../src/*.h"
        "../src/*.cpp"
        )


# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(GTests_run TestMatrix.cpp ${ALLSRC})
target_link_libraries(GTests_run gtest gtest_main)