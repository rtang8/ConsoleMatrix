#ifndef SMARTMATRIX_H
#define SMARTMATRIX_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <fstream>

#include "smartarray.h"

using namespace std;

enum smartMatrixErrors {
    BAD_ROW_VALUE,
    BAD_COLUMN_VALUE,
    MATRIX_OUT_OF_BOUNDS,
    ADDITION_NOT_POSSIBLE,
    MULTIPLICATION_NOT_POSSIBLE
};

class smartMatrix {

private:
    smartArray *matrix;
    uint m_row, m_col;
    mixedNumber highestNum = 0;

    void copy(const smartMatrix &other);
    void destroy();
    uint numDigit(uint i);

public:
    smartMatrix();
    smartMatrix(int, int, bool zero = true);
    ~smartMatrix();
    smartMatrix(const smartMatrix &other);
    smartMatrix &operator=(const smartMatrix &other);

    uint size() const;
    int highest();
    void zeroMatrix();
    void resize(int row, int col, bool zero = true);

    smartArray &operator[](int index);
    smartArray  operator[](int index) const;

    friend
    smartMatrix operator+(const smartMatrix &x, const smartMatrix &y);
    friend
    smartMatrix operator*(const smartMatrix &x, const smartMatrix &y);

    friend
    ostream& operator<<(ostream &out,smartMatrix list);

    friend
    istream& operator>>(istream &in, smartMatrix &list);

};
#endif // SMARTMATRIX_H
