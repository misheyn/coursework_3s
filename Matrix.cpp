#include "Matrix.h"
#include <stdexcept>
#include <fstream>

using namespace std;

Matrix::Matrix() {
    order = 0;
    matrix = nullptr;
}

Matrix::Matrix(int order) : order(order) {
    if (order < 1 || isalpha((char) order))
        throw invalid_argument("Invalid matrix order");
    matrix = new double *[order];
    for (int i = 0; i < order; i++) {
        matrix[i] = new double[order];
    }
    for (int i = 0; i < order; i++)
        for (int j = 0; j < order; j++)
            matrix[i][j] = 0;
}

Matrix::Matrix(const Matrix &obj) {
    order = obj.order;
    matrix = new double *[obj.order];
    for (int i = 0; i < order; i++) {
        matrix[i] = new double[obj.order];
    }
    for (int i = 0; i < obj.order; i++)
        for (int j = 0; j < obj.order; j++)
            matrix[i][j] = obj.matrix[i][j];
}

Matrix::~Matrix() {
    for (int i = 0; i < order; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

double Matrix::getMatrix(int i, int j) const {
    if (i >= order || j >= order || i < 0 || j < 0)
        throw out_of_range("Out of range matrix");
    return matrix[i][j];
}

void Matrix::setMatrix(int i, int j, double value) {
    if (i >= order || j >= order || i < 0 || j < 0)
        throw out_of_range("Out of range matrix");
    matrix[i][j] = value;
}

char *Matrix::toString() {
    int l, len;
    if (matrix == nullptr) return nullptr;
    l = digitCount(matrix, order);
    char *buf = new char[l + order * order];
    len = 0;
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            len += std::sprintf(buf + len * sizeof(char), "%g", matrix[i][j]);
            if (j != order - 1) {
                len += strCat(buf, len, (' '));
            }
        }
        if (i != order - 1) {
            len += strCat(buf, len, ('\n'));

        } else {
            len += strCat(buf, len, ('\0'));
        }
    }
    return buf;
}

void Matrix::transposeMatrix() {
    Matrix other(order);
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            other.matrix[i][j] = matrix[j][i];
        }
    }
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

int Matrix::strCat(char *buf, int len, char elem) {
    return std::sprintf(buf + len * sizeof(char), "%c", elem);
}

int Matrix::digitCount(double **_matrix, int _order) {
    Matrix other(_order);
    for (int i = 0; i < _order; i++) {
        for (int j = 0; j < _order; j++) {
            other.matrix[i][j] = _matrix[j][i];
        }
    }
    int len;
    len = 0;
    for (int i = 0; i < _order; i++) {
        for (int j = 0; j < _order; j++) {
            while (other.matrix[i][j] > 0) {
                len++;
                other.matrix[i][j] = other.matrix[i][j] / 10;
            }
        }
    }
    return len;
}

Matrix operator+(const Matrix &m_1, const Matrix &m_2) {
    if (m_2.order != m_1.order || m_2.order > m_1.order || m_2.order < m_1.order)
        throw logic_error("Add/subtract matrices of different orders");
    Matrix temp(m_1.order);
    for (int i = 0; i < m_1.order; i++) {
        for (int j = 0; j < m_1.order; j++) {
            temp.matrix[i][j] = m_1.matrix[i][j] + m_2.matrix[i][j];
        }
    }
    return temp;
}

Matrix operator-(const Matrix &m_1, const Matrix &m_2) {
    if (m_2.order != m_1.order)
        throw logic_error("Add/subtract matrices of different orders");
    Matrix temp(m_1.order);
    for (int i = 0; i < m_1.order; i++) {
        for (int j = 0; j < m_1.order; j++) {
            temp.matrix[i][j] = m_1.matrix[i][j] - m_2.matrix[i][j];
        }
    }
    return temp;
}

Matrix &Matrix::operator=(const Matrix &new_m) {
    if (this != &new_m) {
        for (int i = 0; i < order; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        order = new_m.order;
        matrix = new double *[new_m.order];
        for (int i = 0; i < order; i++) {
            matrix[i] = new double[new_m.order];
        }
        for (int i = 0; i < new_m.order; i++) {
            for (int j = 0; j < new_m.order; j++) {
                matrix[i][j] = new_m.matrix[i][j];
            }
        }
    }
    return *this;
}

double &Matrix::operator()(int i, int j) {
    if (i > order || j > order || i < 0 || j < 0)
        throw out_of_range("Out of range matrix");
    return matrix[i][j];
}

double Matrix::operator()() {
    int scale = order;
    double **_matrix;
    double first, mult;
    double det = 1;
    _matrix = new double *[order];
    for (int i = 0; i < order; i++) {
        _matrix[i] = new double[order];
    }

    for (int i = 0; i < order; i++)
        for (int j = 0; j < order; j++)
            _matrix[i][j] = matrix[i][j];

    while (scale > 1) {
        if (_matrix[order - scale][order - scale] == 0) return 0;
        first = _matrix[order - scale][order - scale];
        for (int i = order - scale + 1; i < order; ++i) {
            mult = _matrix[i][order - scale] / first;
            for (int j = order - scale; j < order; ++j) {
                _matrix[i][j] -= _matrix[order - scale][j] * mult;
            }
        }
        scale--;
    }
    for (int i = 0; i < order; ++i) det *= _matrix[i][i];
    for (int i = 0; i < order; i++) {
        delete[] _matrix[i];
    }
    delete[] _matrix;

    return det;
}

double Matrix::summary() const {
    double sum = 0;
    for (int i = 0; i < this->order; ++i) {
        for (int j = 0; j < this->order; ++j) {
            sum += this->matrix[i][j];
        }
    }
    return sum;
}

bool operator<(const Matrix &m1, const Matrix &m2) {
    double s1, s2;
    s1 = m1.summary();
    s2 = m2.summary();
    return s1 < s2;
}

ostream &operator<<(ostream &os, const Matrix &m) {
    os << m.order << "\n";
    for (int i = 0; i < m.order; ++i) {
        for (int j = 0; j < m.order; ++j) {
            os << m.matrix[i][j];
            if (j != m.order - 1) os << " ";
        }
        if (i != m.order - 1) os << "\n";
    }
    return os;
}

istream &operator>>(istream &is, Matrix &m) {
    is >> m.order;
    m.matrix = new double *[m.order];
    for (int i = 0; i < m.order; i++) {
        m.matrix[i] = new double[m.order];
    }
    for (int i = 0; i < m.order; ++i) {
        for (int j = 0; j < m.order; ++j) {
            is >> m.matrix[i][j];
        }
    }
    return is;
}

ofstream &BinaryOut(ofstream &os, Matrix &m) {
    os.write((char *) &m.order, sizeof(int));
    for (int i = 0; i < m.order; ++i) {
        for (int j = 0; j < m.order; ++j) {
            os.write((char *) &m.matrix[i][j], sizeof(double));
        }
    }
    return os;
}

ifstream &BinaryIn(ifstream &is, Matrix &m) {
    is.read((char *) &m.order, sizeof(int));
    m.matrix = new double *[m.order];
    for (int i = 0; i < m.order; i++) {
        m.matrix[i] = new double[m.order];
    }
    for (int i = 0; i < m.order; ++i) {
        for (int j = 0; j < m.order; ++j) {
            is.read((char *) &m.matrix[i][j], sizeof(double));
        }
    }
    return is;
}

