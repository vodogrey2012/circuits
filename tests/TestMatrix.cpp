//
// Created by Yauheni Sharamed on 21.11.2021.
//

#include "gtest/gtest.h"
#include "../src/Matrix.h"

TEST(test_case_name, test_name)
{
    Matrix m1(2, 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}