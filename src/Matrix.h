//
// Created by Yauheni Sharamed on 21.11.2021.
//

#ifndef CIRCUITS_MATRIX_H
#define CIRCUITS_MATRIX_H

#include <algorithm>
#include <vector>
#include <cassert>
#include <iostream>

template <typename T>
class Matrix {
public:
    Matrix():
            i_(0),
            j_(0){}

    explicit Matrix(int i, int j):
            i_(i),
            j_(j){
        try{
            matrix_.resize(i);
            for(auto & it : matrix_ )
                it.resize(j);
        }
        catch (std::bad_alloc & ba){
            std::cerr << "bad_alloc caught: " << ba.what();
        }
    }

    Matrix(const Matrix &m) :
            i_(m.GetIDem()),
            j_(m.GetJDem()){
        try{
            matrix_.resize(m.GetIDem());
            for(auto & it : matrix_ )
                it.resize(m.GetJDem());
            for(int x = 0; x < i_; ++x)
                for(int y = 0; y < j_; ++y)
                    matrix_[x][y] = m[x][y];
        }
        catch (...){
            std::exception_ptr p = std::current_exception();
            std::cerr << (p ? p.__cxa_exception_type()->name() : "null") << std::endl;
        }
    }

    Matrix(Matrix&& mm) noexcept :
            i_(mm.i_),
            j_(mm.j_),
            matrix_(std::move(mm.matrix_)){}

    ~Matrix()= default;
    int GetIDem() const{
        return i_;
    }

    int GetJDem() const{
        return j_;
    }

    Matrix<T> Transponse(){
        Matrix<T> ret(j_, i_);
        for(int x = 0; x < i_; ++x)
            for(int y = 0; y < j_; ++y)
                ret[y][x] = matrix_[x][y];
        return ret;
    }

    T Det() const {
        assert(i_ == j_ && "Invalid dimensions for Det operation");
        auto save = matrix_;
        return Determinant(save);
    }

    Matrix Inv(){
        assert(i_ == j_ && "Invalid dimensions for Inv operation");
        Matrix<T> ret(i_, j_);
        auto det = Det();

        if(i_ == 1){
            ret[0][0] = 1/det;
            return ret;
        }

        Matrix<T> minor(i_ - 1, j_ - 1);
        for(size_t x = 0; x < i_; ++x){
            for(size_t y = 0; y < j_; ++y){
                for(size_t xx = 0; xx < i_ - 1; ++xx){
                    for(size_t yy = 0; yy < j_ - 1; ++yy) {
                        minor[xx][yy] = matrix_[xx < x ? xx : xx + 1][yy < y ? yy : yy + 1];
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

    Matrix Inv(T det){
        assert(i_ == j_ && "Invalid dimensions for Inv operation");
        Matrix<T> ret(i_, j_);

        if(i_ == 1){
            ret[0][0] = 1/det;
            return ret;
        }
        Matrix<T> minor(i_ - 1, j_ - 1);
        for(size_t x = 0; x < i_; ++x){
            for(size_t y = 0; y < j_; ++y){
                for(size_t xx = 0; xx < i_ - 1; ++xx){
                    for(size_t yy = 0; yy < j_ - 1; ++yy) {
                        minor[xx][yy] = matrix_[xx < x ? xx : xx + 1][yy < y ? yy : yy + 1];
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

    std::vector<double> Gauss(std::vector<T> C){
        assert(i_ == j_ &&
               i_ == C.size() && "Invalid dimensions for Gauss calulation");

        std::vector<std::vector<double>> A;
        try{
            A.resize(i_);
            for(auto & it : A )
                it.resize(j_ + 1);
        }
        catch (std::bad_alloc & ba){
            std::cerr << "bad_alloc caught: " << ba.what();
        }

        auto n = i_;

        for(auto x = 0; x < A.size(); x++)
            for(auto y = 0; y < A.size(); y++)
                A[x][y] = matrix_[x][y];

        for(auto x = 0; x < A.size(); x++)
            A[x][n] = C[x];

        int index;
        for (int l = 0; l < n; l++) {
            double max = std::abs(A[l][l]);
            index = l;
            for (int i = l+1; i < n; i++) {
                if (std::abs(A[i][l]) > max) {
                    max = abs(A[i][l]);
                    index = i;
                }
            }
            std::swap(A[l], A[index]);

            for (int i = 0; i < n; i++)
                for (int j = 0; j < n+1; j++)
                    if (std::abs(A[i][j]) < 1e-18) A[i][j] = 0;

            if(std::abs(A[l][l]) < 1e-18){
                std::cerr << "Degenerated matrix!" <<std::endl;
                std::vector<double> ret;
                ret.resize(0);
                return ret;
            }

            for (int i = l+1; i < n; i++) {
                double tmp = A[i][l] / A[l][l];
                for (int j = n; j >= l; j--) //Считаем от последнего эл-та в строке, т.е. вектора b
                    A[i][j] -= tmp * A[l][j];
            }
        }

        std::vector<double> x;
        try {
            x.resize(n);
        }
        catch (std::bad_alloc & ba){
            std::cerr << "bad_alloc caught: " << ba.what();
        }
        x[n-1] = A[n-1][n]/A[n-1][n-1];
        for (int i = n - 2; i >= 0; i--) {
            x[i] = A[i][n];
            for (int j = i+1 ; j < n; j++)
                x[i] -= A[i][j] * x[j];
            x[i] = x[i]/A[i][i];
        }
        return x;
    }

private:
    T Determinant(std::vector<std::vector<T> >& Buffer) const {
        if (std::all_of(Buffer.begin(), Buffer.end(),
                        [](std::vector<T> & p1) { return *p1.begin() == 0; }))
            return 0;
        auto first = Buffer.begin();
        if (Buffer.size() == 1)
            return *first->begin();
        for (auto i = Buffer.begin() + 1, end = Buffer.end(); i != end; ++i) {
            if(std::abs(*first->begin()) < 1e-18)
                continue;
            T TMP = *i->begin() / *first->begin();
            std::transform(first->begin(), first->end(), i->begin(), i->begin(),
                           [&TMP](const T& value1, const T& value2)->T {
                               return value2 - value1 * TMP;
                           });
        }
        std::vector<std::vector<T> > matrix(Buffer.size() - 1);
        for (auto i = Buffer.begin() + 1, end = Buffer.end(), Tmp = matrix.begin(); i != end; ++i)
            std::copy(i->begin() + 1, i->end(), back_inserter(*Tmp++));
        return *first->begin() * Determinant(matrix);
    }

public:
    std::vector<T> & operator[](int n){
        return matrix_[n];
    }

    const std::vector<T> & operator[](int n) const{
        return matrix_[n];
    }

    friend Matrix<T> operator+(const Matrix<T> & m1, const Matrix<T> & m2){
        assert(m1.GetIDem() == m2.GetIDem() && m1.GetJDem() == m2.GetJDem() && "Invalid dimensions for + operation");
        Matrix<T> res(m1.GetIDem(), m1.GetJDem());
        for(int x = 0; x < res.GetIDem(); ++x)
            for(int y = 0; y < m1.GetJDem(); ++y)
                res[x][y] = m1[x][y] + m2[x][y];
        return res;
    };

    friend Matrix<T> operator-(const Matrix<T> & m1, const Matrix<T> & m2){
        assert(m1.GetIDem() == m2.GetIDem() && m1.GetJDem() == m2.GetJDem() && "Invalid dimensions for - operation");
        Matrix<T> res(m1.GetIDem(), m1.GetJDem());
        for(int x = 0; x < res.GetIDem(); ++x)
            for(int y = 0; y < res.GetJDem(); ++y)
                res[x][y] = m1[x][y] - m2[x][y];
        return res;
    }

    friend Matrix<T> operator*(const Matrix<T> & m1, const Matrix<T> & m2){
        assert(m2.GetIDem() == m1.GetJDem() && "Invalid dimensions for * operation");
        Matrix<T> res(m1.GetIDem(), m2.GetJDem());
        for(int x = 0; x < m1.GetIDem(); ++x)
            for(int y = 0; y < m2.GetJDem(); ++y)
                for(int z = 0; z < m1.GetJDem(); ++z){
                    res[x][y] += m1[x][z]*m2[z][y];
                    }
        return res;
    }

    template <typename N>
    friend Matrix<T> operator*(const Matrix<T> & m1, const N & factor){
        Matrix<T> res(m1.GetIDem(), m1.GetJDem());
        for(int x = 0; x < m1.GetIDem(); ++x)
            for(int y = 0; y < m1.GetJDem(); ++y)
                res[x][y] = m1[x][y]*factor;
        return res;
    }

    template <typename N>
    explicit operator Matrix<N>() {
        Matrix<N> res(i_, j_);
        for (int x = 0; x < i_; ++x)
            for (int y = 0; y < j_; ++y)
                res[x][y] = N(matrix_[x][y]);
        return res;
    }

    friend bool operator==(const Matrix<T> & m1, const Matrix<T> & m2){
        for (size_t i = 0; i < m1.GetIDem(); ++i) {
            for (size_t j = 0; j < m1.GetJDem(); ++j) {
                if (m1[i][j] != m2[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    friend bool operator!=(const Matrix<T> & m1, const Matrix<T> & m2){
        return !(m1 == m2);
    }

    friend std::ostream & operator<<(std::ostream & os, const Matrix<T> & m){
        for(size_t i = 0; i < m.GetIDem(); ++i){
            for(size_t j = 0; j < m.GetJDem(); ++j){
                os << m[i][j] << "\t|";
            }
            os << std::endl;
        }
        return os;
    }

    Matrix<T> & operator=(Matrix<T>&& mm) noexcept {
        if (&mm == this)
            return *this;
        i_ = std::move(mm.i_);
        j_ = std::move(mm.j_);
        matrix_ = std::move(mm.matrix_);
        return *this;
    }

private:
    int i_;
    int j_;
    std::vector<std::vector<T>> matrix_;
};


#endif //CIRCUITS_MATRIX_H
