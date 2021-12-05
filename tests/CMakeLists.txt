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

file(GLOB ALLTST
        "./TB/*.cpp"
        )

configure_file(./e2e/e2e_tb1.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(./e2e/e2e_tb2.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(./e2e/e2e_tb3.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(./e2e/e2e_tb4.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(./e2e/e2e_tb_loops.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(./e2e/e2e_tb4_loops.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(./e2e/e2e_tb_loops1.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(./e2e/e2e_tb_split.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(./e2e/e2e_tb_invalid_parameters.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(./e2e/e2e_long.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

# define testing flow to rename main of project
add_compile_definitions(GTEST)

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(GTests_run TestAll.cpp ${ALLSRC} ${ALLTST} env/TestMain.h)
target_link_libraries(GTests_run gtest)

enable_testing()
include(GoogleTest)
gtest_discover_tests(GTests_run)