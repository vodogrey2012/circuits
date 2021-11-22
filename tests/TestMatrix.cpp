//
// Created by Andrew on 21.11.2021.
//

#include "gtest/gtest.h"
#include "../src/Matrix.h"

TEST(matrix, matrix_equality)
{
    Matrix m1(2, 2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    Matrix m2(2, 2);
    m2[0][0] = 1;
    m2[0][1] = 2;
    m2[1][0] = 3;
    m2[1][1] = 4;

    ASSERT_EQ(m1, m2);

    m2[0][0] = 5;

    ASSERT_NE(m1, m2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}