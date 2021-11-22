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

TEST(matrix, matrix_dims) {
    Matrix m1(4, 5);
    ASSERT_EQ(m1.GetIDem(), 4);
    ASSERT_EQ(m1.GetJDem(), 5);
}

TEST(matrix, matrix_sum) {
    Matrix m1(1, 1);
    m1[0][0] = 1;
    Matrix m2(1, 1);
    m2[0][0] = 2;

    Matrix res(1, 1);
    res[0][0] = 3;
    ASSERT_EQ((m1 + m2), res);
    ASSERT_EQ((m1 - m2).GetIDem(), 1);
    ASSERT_EQ((m1 - m2).GetJDem(), 1);

    Matrix m3(2, 3);
    m3[0][0] = 1;
    m3[1][0] = 2;
    m3[0][2] = 2;
    m3[0][1] = 3;
    m3[1][1] = 4;
    m3[1][2] = 1;


    Matrix m4(2, 3);
    m4[0][0] = 4;
    m4[1][0] = 3;
    m4[0][2] = 3;
    m4[0][1] = 2;
    m4[1][1] = 1;
    m4[1][2] = 4;

    Matrix r = m3 + m4;
    std::cout << r << std::endl;
    for (int i = 0; i < 2; i ++) {
        for (int j = 0; j < 3; j ++) {
            ASSERT_EQ(r[i][j], 5);
        }
    }
    ASSERT_EQ(r.GetIDem(), 2);
    ASSERT_EQ(r.GetJDem(), 3);
}

TEST(matrix, matrix_diff) {
    Matrix m1(1, 1);
    m1[0][0] = 3;
    Matrix m2(1, 1);
    m2[0][0] = 1;

    Matrix res(1, 1);
    res[0][0] = 2;
    ASSERT_EQ((m1 - m2), res);
    ASSERT_EQ((m1 - m2).GetIDem(), 1);
    ASSERT_EQ((m1 - m2).GetJDem(), 1);

    Matrix m3(2, 3);
    m3[0][0] = 1;
    m3[1][0] = 2;
    m3[0][2] = 2;
    m3[0][1] = 3;
    m3[1][1] = 3;
    m3[1][2] = 4;


    Matrix m4(2, 3);
    m4[0][0] = 0;
    m4[1][0] = 1;
    m4[0][2] = 1;
    m4[0][1] = 2;
    m4[1][1] = 2;
    m4[1][2] = 3;

    Matrix r = m3 - m4;

    for (int i = 0; i < 2; i ++) {
        for (int j = 0; j < 3; j ++) {
            ASSERT_EQ(r[i][j], 1);
        }
    }
    ASSERT_EQ(r.GetIDem(), 2);
    ASSERT_EQ(r.GetJDem(), 3);
}

TEST(matrix, multiplication) {
    Matrix m1(2, 2);
    m1[0][0] = 1;
    m1[0][1] = 3;
    m1[1][0] = 2;
    m1[1][1] = 4;

    Matrix m2(2, 2);
    m2[0][0] = 4;
    m2[0][1] = 2;
    m2[1][0] = 3;
    m2[1][1] = 1;

    Matrix res(2, 2);
    res[0][0] = 13;
    res[0][1] = 5;
    res[1][0] = 20;
    res[1][1] = 8;

    ASSERT_EQ(m1 * m2, res);
    ASSERT_EQ((m1 * m2).GetIDem(), 2);
    ASSERT_EQ((m1 * m2).GetJDem(), 2);

    Matrix m3(1, 5);
    m3[0][0] = 1;
    m3[0][1] = 2;
    m3[0][2] = 3;
    m3[0][3] = 4;
    m3[0][4] = 5;

    Matrix m4(5, 1);
    m4[0][0] = 5;
    m4[1][0] = 4;
    m4[2][0] = 3;
    m4[3][0] = 2;
    m4[4][0] = 1;

    res = Matrix(1, 1);
    res[0][0] = 35;

    ASSERT_EQ(m3 * m4, res);
    ASSERT_EQ((m3 * m4).GetIDem(), 1);
    ASSERT_EQ((m3 * m4).GetJDem(), 1);

}

TEST(matrix, factor_multiplication) {
    Matrix m1(2, 2);
    m1[0][0] = 2;
    m1[0][1] = 3;
    m1[1][0] = 2;
    m1[1][1] = 4;

    Matrix res = m1 * 2.5;
    // Matrix m1 has not changed:
    ASSERT_EQ(m1[0][0], 2);
    // Elements of matrix res:
    ASSERT_EQ(res[0][0], 5);
    ASSERT_EQ(res[0][1], 7.5);
    ASSERT_EQ(res[1][0], 5);
    ASSERT_EQ(res[1][1], 10);
    ASSERT_EQ(res.GetIDem(), 2);
    ASSERT_EQ(res.GetJDem(), 2);

    Matrix m2(1, 5);
    m2[0][0] = 1;
    m2[0][1] = 2;
    m2[0][2] = 3;
    m2[0][3] = 4;
    m2[0][4] = 5;

    Matrix res1 = m2 * -2.0;
    ASSERT_EQ(res1[0][0], -2);
    ASSERT_EQ(res1[0][1], -4);
    ASSERT_EQ(res1[0][2], -6);
    ASSERT_EQ(res1[0][3], -8);
    ASSERT_EQ(res1[0][4], -10);

    ASSERT_EQ(res1.GetIDem(), 1);
    ASSERT_EQ(res1.GetJDem(), 5);
}

TEST(matrix, inverse) {
    Matrix m1(2, 2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    Matrix inv = m1.Inv();

    Matrix E(2, 2);
    E[0][0] = 1;
    E[0][1] = 0;
    E[1][0] = 0;
    E[1][1] = 1;

    ASSERT_EQ(m1 * inv, E);
    ASSERT_EQ(inv.GetIDem(), 2);
    ASSERT_EQ(inv.GetJDem(), 2);
}

TEST(matrix, wrong_dimensions) {
    // Test of errors caused by arithmetical operations
    // with matrix of non-matching dimensions.
    Matrix m1(1, 1);
    Matrix m2(1, 2);
    ASSERT_DEATH({
        Matrix res = m1 + m2;
        }, "Invalid dimensions");
    ASSERT_DEATH({
        Matrix res = m1 - m2;
        }, "Invalid dimensions");
    ASSERT_DEATH({
        Matrix res = m2 * m1;
        }, "Invalid dimensions");
}

TEST(matrix, determinant) {
    Matrix m1(2, 2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;

    ASSERT_EQ(m1.Det(), (1*4 - 2*3));

    Matrix m3(3, 3);
    m3[0][0] = 1;
    m3[0][1] = 2;
    m3[0][2] = 3;
    m3[1][0] = 3;
    m3[1][1] = 4;
    m3[1][2] = 5;
    m3[2][0] = 5;
    m3[2][1] = 6;
    m3[2][2] = 7;

    ASSERT_EQ(m3.Det(), 0);
}

TEST(matrix, non_square_det) {
    // Test of errors caused by calculation
    // of determinant of non-square matrix.
    Matrix m(2, 3);
    ASSERT_DEATH({
        double d = m.Det();
        }, "Invalid dimensions");
    Matrix j(3, 2);
    ASSERT_DEATH({
        double d = j.Det();
        }, "Invalid dimensions");
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}