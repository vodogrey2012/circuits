//
// Created by Yauheni Sharamed on 24.11.2021.
//

#include "gtest/gtest.h"
#include "../../src/Matrix.h"

TEST(matrix, matrix_constructors) {
    Matrix<double> m1(3, 2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;
    m1[2][0] = 4;
    m1[2][1] = 4;

    Matrix<double> m2 = m1;

    ASSERT_EQ(m1, m2);
    ASSERT_EQ(m1.GetIDem(), m2.GetIDem());
    ASSERT_EQ(m1.GetJDem(), m2.GetJDem());
}

Matrix<double> generateItem()
{
    Matrix<double> item(1, 2);
    item[0][0] = 1;
    item[0][1] = -1;
    return item; // это возвращаемое значение приведет к вызову конструктора перемещения
}

TEST(matrix, matrix_assign_move) {
    Matrix<double> m1;
    m1 = generateItem();

    ASSERT_EQ(m1[0][0], 1);
    ASSERT_EQ(m1[0][1], -1);
    ASSERT_EQ(m1.GetIDem(), 1);
    ASSERT_EQ(m1.GetJDem(), 2);
}


TEST(matrix, matrix_equality) {
Matrix<double> m1(2, 2);
m1[0][0] = 1;
m1[0][1] = 2;
m1[1][0] = 3;
m1[1][1] = 4;

Matrix<double> m2(2, 2);
m2[0][0] = 1;
m2[0][1] = 2;
m2[1][0] = 3;
m2[1][1] = 4;

ASSERT_EQ(m1, m2);

m2[0][0] = 5;

ASSERT_NE(m1, m2);
}

TEST(matrix, matrix_dims) {
Matrix<double> m1(4, 5);
ASSERT_EQ(m1.GetIDem(), 4);
ASSERT_EQ(m1.GetJDem(), 5);
}

TEST(matrix, matrix_sum) {
Matrix<int> m1(1, 1);
m1[0][0] = 1;
Matrix<int> m2(1, 1);
m2[0][0] = 2;

Matrix<int> res(1, 1);
res[0][0] = 3;
ASSERT_EQ((m1 + m2), res);
ASSERT_EQ((m1 - m2).GetIDem(), 1);
ASSERT_EQ((m1 - m2).GetJDem(), 1);

Matrix<int> m3(2, 3);
m3[0][0] = 1;
m3[1][0] = 2;
m3[0][2] = 2;
m3[0][1] = 3;
m3[1][1] = 4;
m3[1][2] = 1;

Matrix<int> m4(2, 3);
m4[0][0] = 4;
m4[1][0] = 3;
m4[0][2] = 3;
m4[0][1] = 2;
m4[1][1] = 1;
m4[1][2] = 4;

Matrix<int> r = m3 + m4;
for (int i = 0; i < 2; i ++) {
for (int j = 0; j < 3; j ++) {
ASSERT_EQ(r[i][j], 5);
}
}
ASSERT_EQ(r.GetIDem(), 2);
ASSERT_EQ(r.GetJDem(), 3);

Matrix<double> m5(2, 2);
m5[0][0] = 6.5;
m5[0][1] = 2.2;
m5[1][0] = 3.5;
m5[1][1] = 4.1;
Matrix<double> m6(2, 2);
m6[0][0] = 1.3;
m6[0][1] = 1.2;
m6[1][0] = 0.5;
m6[1][1] = 3.1;

ASSERT_DOUBLE_EQ((m5+m6)[0][0], 7.8);
ASSERT_DOUBLE_EQ((m5+m6)[0][1], 3.4);
ASSERT_DOUBLE_EQ((m5+m6)[1][0], 4.0);
ASSERT_DOUBLE_EQ((m5+m6)[1][1], 7.2);
ASSERT_EQ((m5+m6).GetIDem(), 2);
ASSERT_EQ((m5+m6).GetJDem(), 2);
}

TEST(matrix, matrix_diff) {
Matrix<double> m1(1, 1);
m1[0][0] = 3;
Matrix<double> m2(1, 1);
m2[0][0] = 1;

Matrix<double> res(1, 1);
res[0][0] = 2;
ASSERT_EQ((m1 - m2), res);
ASSERT_EQ((m1 - m2).GetIDem(), 1);
ASSERT_EQ((m1 - m2).GetJDem(), 1);

Matrix<double> m3(2, 3);
m3[0][0] = 1;
m3[1][0] = 2;
m3[0][2] = 2;
m3[0][1] = 3;
m3[1][1] = 3;
m3[1][2] = 4;


Matrix<double> m4(2, 3);
m4[0][0] = 0;
m4[1][0] = 1;
m4[0][2] = 1;
m4[0][1] = 2;
m4[1][1] = 2;
m4[1][2] = 3;

Matrix<double> r = m3 - m4;

for (int i = 0; i < 2; i ++) {
for (int j = 0; j < 3; j ++) {
ASSERT_EQ(r[i][j], 1);
}
}
ASSERT_EQ(r.GetIDem(), 2);
ASSERT_EQ(r.GetJDem(), 3);
}

TEST(matrix, matrix_transpose) {
Matrix<double> m1(2, 3);
m1[0][0] = 1;
m1[0][1] = 2;
m1[0][2] = 3;
m1[1][0] = 4;
m1[1][1] = 5;
m1[1][2] = 6;

Matrix<double> exp(3, 2);
exp[0][0] = 1;
exp[0][1] = 4;
exp[1][0] = 2;
exp[1][1] = 5;
exp[2][0] = 3;
exp[2][1] = 6;

auto res = m1.Transponse();

ASSERT_EQ(res, exp);
ASSERT_EQ(res.GetIDem(), exp.GetIDem());
ASSERT_EQ(res.GetJDem(), exp.GetJDem());
}

TEST(matrix, multiplication) {
Matrix<double> m1(2, 2);
m1[0][0] = 1;
m1[0][1] = 3;
m1[1][0] = 2;
m1[1][1] = 4;

Matrix<double> m2(2, 2);
m2[0][0] = 4;
m2[0][1] = 2;
m2[1][0] = 3;
m2[1][1] = 1;

Matrix<double> res(2, 2);
res[0][0] = 13;
res[0][1] = 5;
res[1][0] = 20;
res[1][1] = 8;

ASSERT_EQ(m1 * m2, res);
ASSERT_EQ((m1 * m2).GetIDem(), 2);
ASSERT_EQ((m1 * m2).GetJDem(), 2);

Matrix<double> m3(1, 5);
m3[0][0] = 1;
m3[0][1] = 2;
m3[0][2] = 3;
m3[0][3] = 4;
m3[0][4] = 5;

Matrix<double> m4(5, 1);
m4[0][0] = 5;
m4[1][0] = 4;
m4[2][0] = 3;
m4[3][0] = 2;
m4[4][0] = 1;

res = Matrix<double>(1, 1);
res[0][0] = 35;

ASSERT_EQ(m3 * m4, res);
ASSERT_EQ((m3 * m4).GetIDem(), 1);
ASSERT_EQ((m3 * m4).GetJDem(), 1);

}

TEST(matrix, factor_multiplication) {
Matrix<double> m1(2, 2);
m1[0][0] = 2;
m1[0][1] = 3;
m1[1][0] = 2;
m1[1][1] = 4;

Matrix<double> res = m1 * 2.5;
// Matrix m1 has not changed:
ASSERT_EQ(m1[0][0], 2);
// Elements of matrix res:
ASSERT_EQ(res[0][0], 5);
ASSERT_EQ(res[0][1], 7.5);
ASSERT_EQ(res[1][0], 5);
ASSERT_EQ(res[1][1], 10);
ASSERT_EQ(res.GetIDem(), 2);
ASSERT_EQ(res.GetJDem(), 2);

Matrix<double> m2(1, 5);
m2[0][0] = 1;
m2[0][1] = 2;
m2[0][2] = 3;
m2[0][3] = 4;
m2[0][4] = 5;

Matrix<double> res1 = m2 * -2.0;
ASSERT_EQ(res1[0][0], -2);
ASSERT_EQ(res1[0][1], -4);
ASSERT_EQ(res1[0][2], -6);
ASSERT_EQ(res1[0][3], -8);
ASSERT_EQ(res1[0][4], -10);

ASSERT_EQ(res1.GetIDem(), 1);
ASSERT_EQ(res1.GetJDem(), 5);
}

TEST(matrix, wrong_dimensions) {
// Test of errors caused by arithmetical operations
// with matrix of non-matching dimensions.
Matrix<double> m1(1, 1);
Matrix<double> m2(1, 2);
ASSERT_DEATH({
Matrix<double> res = m1 + m2;
}, "Invalid dimensions");
ASSERT_DEATH({
Matrix<double> res = m1 - m2;
}, "Invalid dimensions");
ASSERT_DEATH({
Matrix<double> res = m2 * m1;
}, "Invalid dimensions");
}

TEST(matrix, type_casting) {
Matrix<int> m_int(1, 1);
m_int[0][0] = 1;
ASSERT_EQ(m_int[0][0], 1);

// Has no effect with int, as casted to 1.
m_int[0][0] = 1.1;
ASSERT_EQ(m_int[0][0], 1);

// Now has effect because new matrix contains doubles:
Matrix<double> m_d = Matrix<double>(m_int);
m_d[0][0] = 1.1;
ASSERT_EQ(m_d[0][0], 1.1);
}

TEST(matrix, matrix_casting) {
Matrix<int> m1(2, 2);
m1[0][0] = 1;
m1[0][1] = 2;
m1[1][0] = 3;
m1[1][1] = 4;

Matrix<double> m2 = Matrix<double>(m1);

Matrix<double> exp(2, 2);
exp[0][0] = 1;
exp[0][1] = 2;
exp[1][0] = 3;
exp[1][1] = 4;

ASSERT_EQ(m2, exp);
}


TEST(matrix, gauss1) {
    Matrix<double> Am(2, 2);
    Matrix<double> Cm(2, 1);

    Am[0][0] = 1;
    Am[0][1] = 2;
    Am[1][0] = 3;
    Am[1][1] = 4;

    std::vector<double> C = {5, 6};

    auto res = Am.Gauss(C.begin(), C.end());
    std::vector<double> exp = {-4, 4.5};

    ASSERT_EQ(res.size(), exp.size());
    for (int i = 0; i < exp.size(); ++i) {
        EXPECT_NEAR(res[i], exp[i], 0.01);
    }
}


TEST(matrix, gauss2) {
    Matrix<double> Am(2, 2);
    Matrix<double> Cm(2, 1);

    Am[0][0] = 1;
    Am[0][1] = 2;
    Am[1][0] = 0;
    Am[1][1] = 4;

    std::vector<double> C = {5, 6};

    auto res = Am.Gauss(C.begin(), C.end());
    std::vector<double> exp = {2, 1.5};

    ASSERT_EQ(res.size(), exp.size());
    for (int i = 0; i < exp.size(); ++i) {
        EXPECT_NEAR(res[i], exp[i], 0.01);
    }
}