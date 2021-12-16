//
// Created by Yauheni Sharamed on 24.11.2021.
//

#include "gtest/gtest.h"
#include "../env/TestMain.h"
#include <regex>

std::vector<double> CalcCircuit(const char* file);
std::vector<std::pair<double, double>> CalcCircuitAC(const char* file);

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
    std::vector<double> exp = {-0.56, -3.125, -3.125, -0.56, -0.56, 2.565, 3.63, -1.38, -1.38, 3.63, 3.63, 5.01, 1, 0};
    auto res = CalcCircuit(file);

    ASSERT_EQ(res.size(), exp.size());
    for (int i = 0; i < exp.size(); ++i) {
        EXPECT_NEAR(res[i], exp[i], 0.01);
    }
}

TEST(matrix, e2e_tb_invalid_parameters) {
    const char* file = "e2e_tb_invalid_parameters.txt";
    auto res = CalcCircuit(file);
    ASSERT_EQ(res.size(), 0);
}

TEST(matrix, e2e_tb5) {
    const char* file = "e2e_tb5.txt";
    std::vector<double> exp = {0, 0, 0, 1.68142, -1.68142};
    auto res = CalcCircuit(file);

    ASSERT_EQ(res.size(), exp.size());
    for (int i = 0; i < exp.size(); ++i) {
        EXPECT_NEAR(res[i], exp[i], 0.01);
    }
}

TEST(matrix, e2e_ac_tb1) {
    const char* file = "e2e_ac_tb1.txt";
    std::vector<double> expampl = {0.44, 0.63, 1.08, 0.08, 0.37, 0.71};
    std::vector<double> expfi = {0, 0, 3.14, 0, 0, 0};
    assert(expampl.size() == expfi.size() && "Invalid test exp vectors");
    auto res = CalcCircuitAC(file);

    ASSERT_EQ(res.size(), expampl.size());
    for (int i = 0; i < expampl.size(); ++i) {
        EXPECT_NEAR(res[i].first, expampl[i], 0.01);
        EXPECT_NEAR(res[i].second, expfi[i], 0.01);
    }
}

TEST(matrix, e2e_long) {
    const char* file = "e2e_long.txt";
    auto res = CalcCircuit(file);

    ASSERT_EQ(res.size(), 1225);
    for(auto & res1 : res){
        if(std::abs(res1) > 1e-18){
            ASSERT_TRUE(true);
            break;
        }
    }

}

TEST(matrix, e2e_long1) {
    const char* file = "e2e_long1.txt";
    auto res = CalcCircuit(file);

    ASSERT_EQ(res.size(), 4900);
    for(auto & res1 : res){
        if(std::abs(res1) > 1e-18){
            ASSERT_TRUE(false);
            break;
        }
    }

}

TEST(matrix, e2e_ac_long) {
    const char* file = "e2e_ac_long.txt";
    auto res = CalcCircuitAC(file);

    ASSERT_EQ(res.size(), 1225);
    for(auto & res1 : res){
        if(std::abs(res1.first) > 1e-18){
            ASSERT_TRUE(true);
            break;
        }
        if(std::abs(res1.second) > 1e-18){
            ASSERT_TRUE(true);
            break;
        }
    }

}

 TEST(matrix, e2e_ac_long1) {
    const char* file = "e2e_ac_long1.txt";
    auto res = CalcCircuitAC(file);

    ASSERT_EQ(res.size(), 4900);
    for(auto & res1 : res){
        if(std::abs(res1.first) > 1e-18){
            ASSERT_TRUE(false);
            break;
        }
        if(std::abs(res1.second) > 1e-18){
            ASSERT_TRUE(false);
            break;
        }
    }

}

std::vector<double> CalcCircuit(const char* file){
    int     argc = 2;
    char    arg0[] = "test_main";
    char*   arg1 = strdup(file);

    char*   argv[] = { arg0, arg1};

    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream strCout;
    std::cout.rdbuf( strCout.rdbuf() );
    test_main<double>(argc, argv);
    std::cout.rdbuf( oldCoutStreamBuf );

    std::string out = strCout.str();

    std::regex re(": (-?\\d+(?:\\.\\d+)?)");

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

std::vector<std::pair<double, double>> CalcCircuitAC(const char* file){
    int     argc = 2;
    char    arg0[] = "test_main";
    char*   arg1 = strdup(file);

    char*   argv[] = { arg0, arg1};

    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::ostringstream strCout;
    std::cout.rdbuf( strCout.rdbuf() );
    test_main<std::complex<double>>(argc, argv);
    std::cout.rdbuf( oldCoutStreamBuf );

    std::string out = strCout.str();

    std::regex re(": (-?\\d+(?:\\.\\d+)?) A, (-?\\d+(?:\\.\\d+)?)");

    auto words_begin =
            std::sregex_iterator(out.begin(), out.end(), re);
    auto words_end = std::sregex_iterator();

    std::vector<std::pair<double, double>> ret;
    for(std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        double res1 = 0;
        double res2 = 0;
        std::istringstream (match[1]) >> res1;
        std::istringstream (match[2]) >> res2;
        ret.emplace_back(std::pair<double, double>(res1, res2));
    }
    return ret;
}
