//
// Created by Yauheni Sharamed on 21.11.2021.
//

#include <iostream>
#include <algorithm>
#include "Matrix.h"

Matrix::Matrix(int i, int j) {
    _i = i;
    _j = j;
    _matrix.resize(i);
    for(auto & it : _matrix )
        it.resize(j);
}

int Matrix::GetIDem() const {
    return _i;
}

int Matrix::GetJDem() const {
    return _j;
}

Matrix operator+(const Matrix &m1, const Matrix &m2) {
    assert(m1.GetIDem() == m2.GetIDem() && m1.GetJDem() == m2.GetJDem() && "Invalid dimensions for + operation");
    Matrix res(m1.GetIDem(), m1.GetJDem());
    for(int x = 0; x < res.GetIDem(); ++x)
        for(int y = 0; y < m1.GetJDem(); ++y)
            res[x][y] = m1[x][y] + m2[x][y];
    return res;
}

Matrix operator-(const Matrix &m1, const Matrix &m2) {
    assert(m1.GetIDem() == m2.GetIDem() && m1.GetJDem() == m2.GetJDem() && "Invalid dimensions for - operation");
    Matrix res(m1.GetIDem(), m1.GetJDem());
    for(int x = 0; x < res.GetIDem(); ++x)
        for(int y = 0; y < res.GetJDem(); ++y)
            res[x][y] = m1[x][y] - m2[x][y];
    return res;
}

std::vector<double> &Matrix::operator[](int n) {
    assert(n < _i && "Index out of range");
    return _matrix[n];
}

const std::vector<double> &Matrix::operator[](int n) const {return _matrix[n];}

Matrix operator*(const Matrix &m1, const Matrix &m2) {
    assert(m2.GetIDem() == m1.GetJDem() && "Invalid dimensions for * operation");
    Matrix res(m1.GetIDem(), m2.GetJDem());
    for(int x = 0; x < m1.GetIDem(); ++x)
        for(int y = 0; y < m2.GetJDem(); ++y)
            for(int z = 0; z < m1.GetJDem(); ++z){
                res[x][y] += m1[x][z]*m2[z][y];
            }
    return res;
}

Matrix operator*(const Matrix &m1, const double &factor) {
    Matrix res(m1.GetIDem(), m1.GetJDem());
    for(int x = 0; x < m1.GetIDem(); ++x)
        for(int y = 0; y < m1.GetJDem(); ++y)
                res[x][y] = m1[x][y]*factor;
    return res;
}

Matrix Matrix::Transponse() {
    Matrix ret(_j, _i);
    for(int x = 0; x < _i; ++x)
        for(int y = 0; y < _j; ++y)
            ret[y][x] = _matrix[x][y];
    return ret;
}

Matrix Matrix::operator=(const Matrix &m1) {
    Matrix res(m1.GetIDem(), m1.GetJDem());
    for(int x = 0; x < m1.GetIDem(); ++x)
        for(int y = 0; y < m1.GetJDem(); ++y)
            res[x][y] = m1[x][y];
    return res;
}

double Matrix::Det() {
    assert(_i == _j && "Invalid dimensions for Det operation");
    auto save = _matrix;
    return Determinant(save);
}

class nulled : public std::unary_function<std::vector<double>, bool> {
public:
    bool operator() (const std::vector<double>& Buffer) {
        return !(*Buffer.begin());
    }
};

class chg : public std::binary_function<std::vector<double>, std::vector<double>, bool> {
public:
    bool operator()(const std::vector<double>& Buffer1, const std::vector<double>& Buffer2) {
        return *Buffer1.begin() > *Buffer2.begin();
    }
};

class chg2 : public std::binary_function<std::vector<double>, std::vector<double>, bool> {
public:
    bool operator()(const std::vector<double>& Buffer1, const std::vector<double>& Buffer2) {
        return *Buffer1.begin() < *Buffer2.begin();
    }
};

double Matrix::Determinant(std::vector<std::vector<double>> &Buffer) {
    sort(Buffer.begin(), Buffer.end(), chg2());
    if (std::all_of(Buffer.begin(), Buffer.end(), nulled()))
        return 0;
    auto first = Buffer.begin();
    if (Buffer.size() == 1)
        return *first->begin();
    for (auto i = Buffer.begin() + 1, end = Buffer.end(); i != end; ++i)
    {
        double T = *i->begin() / *first->begin();
        std::transform(first->begin(), first->end(), i->begin(), i->begin(),
                       [&T](const double& value1, const double& value2)->double
                  {
                      return value2 - value1 * T;
                  });
    }
    sort(Buffer.begin() + 1, Buffer.end(), chg());
    std::vector<std::vector<double> > matrix(Buffer.size() - 1);
    for (auto i = Buffer.begin() + 1, end = Buffer.end(), Tmp = matrix.begin(); i != end; ++i)
        copy(i->begin() + 1, i->end(), back_inserter(*Tmp++));
    return *first->begin() * Determinant(matrix);
}

Matrix Matrix::Inv() {
    assert(_i == _j && "Invalid dimensions for Inv operation");
    Matrix ret(_i, _j);
    auto det = Det();

    if(_i == 1){
        ret[0][0] = 1/det;
        return ret;
    }

    for(size_t x = 0; x < _i; ++x){
        for(size_t y = 0; y < _j; ++y){
            Matrix minor(_i-1, _j-1);
            for(size_t xx = 0; xx < _i-1; ++xx){
                for(size_t yy = 0; yy < _j-1; ++yy) {
                    minor[xx][yy] = _matrix[xx < x ? xx : xx+1][yy < y ? yy : yy+1];
                }
            }
            auto minor_det = minor.Det();
            if((x+y)%2 == 1)
                minor_det *= -1.0;
            ret[y][x] = minor_det/det;
        }
    }
    return ret;
}

std::ostream &operator<<(std::ostream &os, const Matrix &m) {
    for(size_t i = 0; i < m._i; ++i){
        for(size_t j = 0; j < m._j; ++j){
            os << m._matrix[i][j] << "\t|";
        }
        os << std::endl;
    }
    return os;
}

bool operator==(const Matrix &m1, const Matrix &m2) {
    for (size_t i = 0; i < m1.GetIDem(); ++i) {
        for (size_t j = 0; j < m1.GetJDem(); ++j) {
            if (m1[i][j] != m2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix &m1, const Matrix &m2) {
    return !(m1==m2);
}

