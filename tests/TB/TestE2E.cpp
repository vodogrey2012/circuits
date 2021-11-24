//
// Created by Yauheni Sharamed on 24.11.2021.
//

#include "gtest/gtest.h"
#include "../env/TestMain.h"
#include <regex>

double CalcCircuit(const char* file, int p1, int p2);

TEST(matrix, e2e_tb1) {
    const char* file = "e2e_tb1.txt";
    EXPECT_NEAR(CalcCircuit(file, 1, 2), -0.56, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 2, 1),  0.56, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 5, 1), -0.56, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 1, 5),  0.56, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 4, 5), -0.56, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 5, 4),  0.56, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 2, 4),  2.565, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 4, 2), -2.565, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 2, 3), -3.125, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 3, 2),  3.125, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 3, 4), -3.125, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 4, 3),  3.125, 0.01);
}

TEST(matrix, e2e_tb2) {
    const char* file = "e2e_tb2.txt";
    EXPECT_NEAR(CalcCircuit(file, 1, 2), 3.63, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 2, 1),-3.63, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 5, 1), 3.63, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 1, 5),-3.63, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 4, 5), 3.63, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 5, 4),-3.63, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 2, 4),  5.01, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 4, 2), -5.01, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 2, 3), -1.38, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 3, 2),  1.38, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 3, 4), -1.38, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 4, 3),  1.38, 0.01);
}

TEST(matrix, e2e_tb3) {
    const char* file = "e2e_tb3.txt";
    EXPECT_NEAR(CalcCircuit(file, 1, 2),-3.94, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 2, 1), 3.94, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 2, 5), 4.46, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 5, 2),-4.46, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 5, 4), 4.46, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 4, 5),-4.46, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 2, 6),-8.4, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 6, 2), 8.4, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 6, 3),-8.4, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 3, 6), 8.4, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 1, 4),-0.256, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 4, 1), 0.256, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 4, 3),  4.21, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 3, 4), -4.21, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 1, 3),  4.19, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 3, 1), -4.19, 0.01);
}

TEST(matrix, e2e_tb4) {
    const char* file = "e2e_tb4.txt";
    EXPECT_NEAR(CalcCircuit(file, 1, 2), 4.69, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 2, 1),-4.69, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 2, 3), 5.24, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 3, 2),-5.24, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 2, 4),-0.553, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 4, 2), 0.553, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 1, 3), 6.53, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 3, 1),-6.53, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 3, 4), 11.77, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 4, 3),-11.77, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 4, 1), 11.22, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 1, 4),-11.22, 0.01);
}

TEST(matrix, e2e_tb_loops) {
    const char* file = "e2e_tb_loops.txt";
    EXPECT_NEAR(CalcCircuit(file, 1, 2), 0, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 2, 1),0, 0.01);

}

TEST(matrix, e2e_tb4_loops) {
    const char* file = "e2e_tb4_loops.txt";
    EXPECT_NEAR(CalcCircuit(file, 1, 2), 4.69, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 2, 1),-4.69, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 2, 3), 5.24, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 3, 2),-5.24, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 2, 4),-0.553, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 4, 2), 0.553, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 1, 3), 6.53, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 3, 1),-6.53, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 3, 4), 11.77, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 4, 3),-11.77, 0.01);

    EXPECT_NEAR(CalcCircuit(file, 4, 1), 11.22, 0.01);
    EXPECT_NEAR(CalcCircuit(file, 1, 4),-11.22, 0.01);
}



double CalcCircuit(const char* file, int p1, int p2){
    int     argc = 4;
    char    arg0[] = "test_main";
    char*   arg1 = strdup(file);

    std::ostringstream sarg2;
    sarg2 << p1;
    std::ostringstream sarg3;
    sarg3 << p2;

    char*   arg2 = strcpy(new char[sarg2.str().length() + 1], sarg2.str().c_str());
    char*   arg3 = strcpy(new char[sarg3.str().length() + 1], sarg3.str().c_str());

    char*   argv[] = { arg0, arg1, arg2, arg3 };

    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream strCout;
    std::cout.rdbuf( strCout.rdbuf() );
    test_main(argc, argv);
    std::cout.rdbuf( oldCoutStreamBuf );

    std::string out = strCout.str();

    std::regex re("I = (-?\\d+(?:\\.\\d+)?)");
    std::smatch match;

    if (std::regex_search(out, match, re)) {
        double ret;
        std::istringstream (match[1]) >> ret;
        return ret;
    }

    return 0;
}
