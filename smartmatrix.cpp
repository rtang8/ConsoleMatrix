#include <iostream>
#include <iomanip>
#include <cmath>
#include "smartmatrix.h"

/// CONSTRUCTORS
///
smartMatrix::smartMatrix(){
    matrix = NULL;
    m_row = 3;
    m_col = 3;
    resize(m_row, m_col, true);
}

smartMatrix::smartMatrix(int row, int col, bool zero) {
    matrix = NULL;
    m_row = row;
    m_col = col;
    resize(m_row, m_col, zero);
}

smartMatrix::~smartMatrix() {
    destroy();
}

smartMatrix::smartMatrix(const smartMatrix &other) {
    copy(other);
}

smartMatrix &smartMatrix::operator=(const smartMatrix &other) {
    if(this != &other) {
        destroy();
        copy(other);
    }
    return *this;
}

/// GENERAL FUNCTIONS
///
uint smartMatrix::size() const {
    return m_row * m_col;
}

// Returns mixedNumber with largest number of characters
int smartMatrix::highest() {
    stringstream ss;
    string temp;
    string tempHigh = "";
    for(uint i = 0; i < m_row; ++i) {
        for(uint j = 0; j < m_col; ++j) {
            ss.str(std::string());
            ss.clear();
            ss << matrix[i][j];
            ss >> temp;

            if(temp.length() > tempHigh.length())
                highestNum = matrix[i][j];

            ss.str(std::string());
            ss.clear();
            ss << highestNum;
            ss >> tempHigh;
        }
    }
    return tempHigh.length();
}

// Resets all the elements of the matrix to 0
void smartMatrix::zeroMatrix() {
    for(uint i = 0; i < m_row; ++i)
        matrix[i].zeroArray();
}

// Destroys old matrix and creates new one with new size
void smartMatrix::resize(int row, int col, bool zero) {
    if(row < 1)
        throw BAD_ROW_VALUE;
    if(col < 1)
        throw BAD_COLUMN_VALUE;
    if(matrix)
        destroy();
    m_row = row;
    m_col = col;
    matrix = new smartArray[m_row]();
    for(uint i = 0; i < m_row; ++i)
        matrix[i] = smartArray(m_col, zero);
    if(matrix == nullptr)
        throw BAD_ROW_VALUE;
}

/// INDEX ACCESSORS
///
smartArray &smartMatrix::operator[](int index) {
    if(index < 0 || index >= m_row)
        throw BAD_ROW_VALUE;
    return matrix[index];
}

smartArray  smartMatrix::operator[](int index) const {
    if(index < 0 || index >= m_row)
        throw BAD_ROW_VALUE;
    return matrix[index];
}

/// PRIVATE FUNCTIONS
///
void smartMatrix::copy(const smartMatrix &other) {
    matrix = NULL;
    resize(other.m_row, other.m_col);
    for(uint i = 0; i < m_row; ++i) {
        for(uint j = 0; j < m_col; ++j) {
            matrix[i][j] = other.matrix[i][j];
        }
    }
}

void smartMatrix::destroy() {
    if(!matrix)
        return;
    zeroMatrix();

    delete[] matrix;
    matrix = NULL;
}

// Returns the number of digits in a number
uint numDigit(uint i) {
    return i > 0 ? (int)log10((double)i) + 1 : 1;
}

/// FRIEND MATH OPERATORS
///

smartMatrix operator+(const smartMatrix &x, const smartMatrix &y) {

    if(x.m_row != y.m_row || x.m_col != y.m_col) {
        throw ADDITION_NOT_POSSIBLE;
    }
    smartMatrix temp(x.m_row, x.m_col);
    for(uint i = 0; i < x.m_row; ++i) {
        for(uint j = 0; j < x.m_col; ++j) {
            temp[i][j] = x[i][j] + y[i][j];
        }
    }

    return temp;
}

smartMatrix operator*(const smartMatrix &x, const smartMatrix &y) {
    if(x.m_col != y.m_row) {
        throw MULTIPLICATION_NOT_POSSIBLE;
    }
    smartMatrix temp(x.m_row, y.m_col);
    mixedNumber numHolder(0);

    for(uint i = 0; i < x.m_row; ++i) {
        for(uint j = 0; j < y.m_col; ++j) {
            for(uint k = 0; k < x.m_col; ++k) {
                numHolder += x[i][k] * y[k][j];
            }
            temp[i][j] = numHolder;
            numHolder = 0;
        }
    }
    return temp;
}

/// FRIEND I/O OPERATORS
///
ostream& operator<<(ostream &out, smartMatrix list) {
    if(&out != &cout) {
        out << "Rows: " << list.m_row << endl;
        out << "Column: " << list.m_col << endl;
        for(uint i = 0; i < list.m_row; ++i) {
            for(uint j = 0; j < list.m_col; ++j) {
                out << "matrix[" << i << "][" << j << "] = " << list[i][j] << endl;
            }
        }
    }
    else {
        // Formatting Functions
        int highest = list.highest();

        stringstream ss;
        string temp;

        for(uint i = 0; i < list.m_row; ++i) {
            out << setw(0) << '|';
            for(uint j = 0; j < list.m_col; ++j) {
                ss.str(std::string());
                ss.clear();
                ss << list[i][j];
                ss >> temp;
                out << setw(highest+2) << setfill(' ') << temp;
            }
            out << '|' << endl;
        }
    }
    return out;
}

istream& operator>>(istream &in, smartMatrix &list) {
    stringstream ss;
    string input;
    uint tempRow, tempCol;

    // If file input, retrieve size and fill array
    if(&in == &cin) {
        std::cout << "Enter number of rows: ";
        in >> tempRow;
        std::cout << "Enter number of columns: ";
        in >> tempCol;
        list.resize(tempRow, tempCol);
        in.clear();
        in.ignore(1000, '\n');

        for(uint i = 0; i < list.m_row; ++i) {
            for(uint j = 0; j < list.m_col; ++j) {
                cout << "matrix[" << i << "][" << j << "] = ";

                in >> list[i][j];
                std::cout << list[i][j] << std::endl;
            }
        }
    }
    // Take in file input
    else {
        getline(in, input);
        ss << input.substr(6);
        ss >> tempRow;

        getline(in, input);
        ss.str(std::string());
        ss.clear();
        ss << input.substr(8);
        ss >> tempCol;

        list.resize(tempRow, tempCol);
        list.m_row = tempRow;
        list.m_col = tempCol;

        //std::cout << "New row value is " << list.m_row << endl;
        //std::cout << "New column value is " << list.m_col << endl;

        for(uint i = 0; i < list.m_row; ++i) {
            for(uint j = 0; j < list.m_col; ++j) {
                getline(in, input);
                ss.str(std::string());
                ss.clear();
                ss << input.substr(input.find(" = ") + 3);
                ss >> list[i][j];
            }
        }
    }
    return in;
}
