//
// Created by Andrew on 11/21/21.
//

#include "gtest/gtest.h"
#include "../Matrix.h"

TEST(test_case_name, test_name)
{
    Matrix m1(2, 2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
