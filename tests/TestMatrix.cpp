//
// Created by Andrew on 21.11.2021.
//

#include "gtest/gtest.h"
#include "../src/Matrix.h"

TEST(matrix, matrix_equality) {
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

TEST(matrix, matrix_sum) {
    Matrix m1(1, 1);
    m1[0][0] = 1;
    Matrix m2(1, 1);
    m2[0][0] = 2;

    Matrix res(1, 1);
    res[0][0] = 3;
    ASSERT_EQ((m1 + m2), res);
}

TEST(matrix, matrix_diff) {
    Matrix m1(1, 1);
    m1[0][0] = 3;
    Matrix m2(1, 1);
    m2[0][0] = 1;

    Matrix res(1, 1);
    res[0][0] = 2;
    ASSERT_EQ((m1 - m2), res);
}

TEST(matrix, wrong_dimensions) {
    Matrix m1(1, 1);
    Matrix m2(1, 2);
    Matrix res = m1 + m2;
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}