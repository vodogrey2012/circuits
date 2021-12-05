//
// Created by Yauheni Sharamed on 24.11.2021.
//

#include "gtest/gtest.h"
#include "../env/TestMain.h"
#include <regex>

std::vector<double> CalcCircuit(const char* file);

TEST(matrix, e2e_tb1) {
    const char* file = "e2e_tb1.txt";
    std::vector<double> exp = {-0.56, -3.125, -3.125, -0.56, -0.56, 2.565};
    auto res = CalcCircuit(file);

    ASSERT_EQ(res.size(), exp.size());
    for (int i = 0; i < exp.size(); ++i) {
        EXPECT_NEAR(res[i], exp[i], 0.01);
    }
}

TEST(matrix, e2e_tb2) {
    const char* file = "e2e_tb2.txt";
    std::vector<double> exp = {3.63, -1.38, -1.38, 3.63, 3.63, 5.01};
    auto res = CalcCircuit(file);

    ASSERT_EQ(res.size(), exp.size());
    for (int i = 0; i < exp.size(); ++i) {
        EXPECT_NEAR(res[i], exp[i], 0.01);
    }
}

TEST(matrix, e2e_tb3) {
    const char* file = "e2e_tb3.txt";
    std::vector<double> exp = {-3.94, 4.46, -8.4, 4.46, -8.4, -0.256, 4.21, 4.19};
    auto res = CalcCircuit(file);

    ASSERT_EQ(res.size(), exp.size());
    for (int i = 0; i < exp.size(); ++i) {
        EXPECT_NEAR(res[i], exp[i], 0.01);
    }
}

TEST(matrix, e2e_tb4) {
    const char* file = "e2e_tb4.txt";
    std::vector<double> exp = {4.69, -0.553, 5.24, 6.53, 11.77, 11.22};
    auto res = CalcCircuit(file);

    ASSERT_EQ(res.size(), exp.size());
    for (int i = 0; i < exp.size(); ++i) {
        EXPECT_NEAR(res[i], exp[i], 0.01);
    }
}

TEST(matrix, e2e_tb_loops) {
    const char* file = "e2e_tb_loops.txt";
    std::vector<double> exp = {1, -1, 0};
    auto res = CalcCircuit(file);

    ASSERT_EQ(res.size(), exp.size());
    for (int i = 0; i < exp.size(); ++i) {
        EXPECT_NEAR(res[i], exp[i], 0.01);
    }
}

TEST(matrix, e2e_tb4_loops) {
    const char* file = "e2e_tb4_loops.txt";
    std::vector<double> exp = {2.35, 2.35, -0.277, -0.277, 5.24, 6.53, 11.77, 11.22 };
    auto res = CalcCircuit(file);

    ASSERT_EQ(res.size(), exp.size());
    for (int i = 0; i < exp.size(); ++i) {
        EXPECT_NEAR(res[i], exp[i], 0.01);
    }
}

TEST(matrix, e2e_tb_loops1) {
    const char* file = "e2e_tb_loops1.txt";
    std::vector<double> exp = {1, 2, -4};
    auto res = CalcCircuit(file);

    ASSERT_EQ(res.size(), exp.size());
    for (int i = 0; i < exp.size(); ++i) {
        EXPECT_NEAR(res[i], exp[i], 0.01);
    }
}

TEST(matrix, e2e_tb_split) {
    const char* file = "e2e_tb_split.txt";
    auto res = CalcCircuit(file);
    ASSERT_EQ(res.size(), 0);
}

TEST(matrix, e2e_tb_invalid_parameters) {
    const char* file = "e2e_tb_invalid_parameters.txt";
    auto res = CalcCircuit(file);
    ASSERT_EQ(res.size(), 0);
}




std::vector<double> CalcCircuit(const char* file){
    int     argc = 2;
    char    arg0[] = "test_main";
    char*   arg1 = strdup(file);

    char*   argv[] = { arg0, arg1};

    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream strCout;
    std::cout.rdbuf( strCout.rdbuf() );
    test_main(argc, argv);
    std::cout.rdbuf( oldCoutStreamBuf );

    std::string out = strCout.str();

    std::regex re("I = (-?\\d+(?:\\.\\d+)?)");

    auto words_begin =
            std::sregex_iterator(out.begin(), out.end(), re);
    auto words_end = std::sregex_iterator();

    std::vector<double> ret;
    for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        double res = 0;
        std::istringstream (match[1]) >> res;
        ret.emplace_back(res);
    }

    return ret;
}
