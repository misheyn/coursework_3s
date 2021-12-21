#ifndef LAB1_3_MATRIX_H
#define LAB1_3_MATRIX_H

#include <iostream>

using namespace std;

class Matrix {

public:
    Matrix();

    Matrix(int order);

    Matrix(const Matrix &obj);

    ~Matrix();

    virtual double getMatrix(int i, int j) const;

    virtual void setMatrix(int i, int j, double value);

    virtual char *toString();

    virtual void transposeMatrix();

    friend Matrix operator+(const Matrix &m_1, const Matrix &m_2);

    friend Matrix operator-(const Matrix &m_1, const Matrix &m_2);

    Matrix &operator=(const Matrix &matrix_2);

    virtual double &operator()(int i, int j);

    double operator()();

    friend bool operator<(const Matrix &m1, const Matrix &m2);

    friend ostream &operator<<(ostream &os, const Matrix &m);

    friend istream &operator>>(istream &is, Matrix &m);

    friend ofstream &BinaryOut(ofstream &os, Matrix &m);

    friend ifstream &BinaryIn(ifstream &is, Matrix &m);

protected:
    int order;
    double **matrix;

    static int strCat(char *buf, int len, char elem);

    static int digitCount(double **_matrix, int _order);

    double summary() const;
};

#endif //LAB1_3_MATRIX_H
