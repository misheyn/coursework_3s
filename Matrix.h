#ifndef LAB1_3_MATRIX_H
#define LAB1_3_MATRIX_H

#include <iostream>
//#include "Tree.h"

using namespace std;


class Matrix {

public:
    Matrix();

    Matrix(int order);

    Matrix(const Matrix &obj);

    ~Matrix();

    virtual double GetMatrix(int i, int j) const;

    virtual void SetMatrix(int i, int j, double value);

    virtual char *toString();

    virtual void TransposeMatrix();

    friend Matrix operator+(const Matrix &m_1, const Matrix &m_2);

    friend Matrix operator-(const Matrix &m_1, const Matrix &m_2);

    Matrix &operator=(const Matrix &matrix_2);

    virtual double &operator()(int i, int j);

    double operator()();

    friend bool operator<(const Matrix &m1, const Matrix &m2);

    friend ostream &operator<<(ostream &os, const Matrix &m);

    friend istream &operator>>(istream &os, Matrix &m);

    friend ofstream &BinaryIn(ofstream &os, Matrix &m);

    friend ifstream &BinaryOut(ifstream &os, Matrix &m);

protected:
    int order;
    double **matrix;

    static int strCat(char *buf, int len, char elem);

    static int digitCount(double **_matrix, int _order);

    double summary() const;
};

#endif //LAB1_3_MATRIX_H
