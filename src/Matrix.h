//
// Created by Yauheni Sharamed on 21.11.2021.
//

#ifndef CIRCUITS_MATRIX_H
#define CIRCUITS_MATRIX_H

#include <vector>
#include <cassert>

class Matrix {
public:
    Matrix(int i, int j);
    ~Matrix()= default;
    int GetIDem() const;
    int GetJDem() const;

public:
    std::vector<double>& operator[](int n);
    const std::vector<double>& operator[](int n) const;
    Matrix Transponse();
    double Det();
    Matrix Inv();
    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    friend Matrix operator-(const Matrix& m1, const Matrix& m2);
    friend Matrix operator*(const Matrix& m1, const Matrix& m2);
    friend Matrix operator*(const Matrix &m1, const double &factor);
    friend bool operator==(const Matrix& m1, const Matrix& m2);
    friend bool operator!=(const Matrix& m1, const Matrix& m2);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    Matrix operator=(const Matrix& m1);
private:
    int _i;
    int _j;
    std::vector<std::vector<double>> _matrix;
    double Determinant(std::vector<std::vector<double> >& Buffer);
};


#endif //CIRCUITS_MATRIX_H
