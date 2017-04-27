#ifndef MIXEDNUMBER_H
#define MIXEDNUMBER_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include "fraction.h"

enum mixedNumberErrors {INPUT_TOO_LONG, BAD_NUM_INPUT, HAS_ALPHABET, IMPROPER_SYMBOL_USE};

class mixedNumber {
private:
    int m_whole;
    Fraction m_frac;
    void copy(const mixedNumber& other);
    int gcd(int p, int q) const;

public:
    mixedNumber();
    ~mixedNumber();
    mixedNumber(double value);
    mixedNumber(int whole, int num = 0, int denom = 1);

    mixedNumber(const mixedNumber& other);
    mixedNumber(const Fraction &other);

    Fraction toFraction() const;
    int getWhole() const;
    Fraction getFrac() const;

    mixedNumber &operator=(const mixedNumber &other);

    mixedNumber &operator+=(const mixedNumber &other);
    mixedNumber &operator-=(const mixedNumber &other);
    mixedNumber &operator*=(const mixedNumber &other);
    mixedNumber &operator/=(const mixedNumber &other);

    friend
    std::ostream &operator<<(std::ostream &out, const mixedNumber &x);
    friend
    std::istream &operator>>(std::istream &in, mixedNumber &x);

    friend
    mixedNumber operator+(const mixedNumber &x, const mixedNumber &y);
    friend
    mixedNumber operator-(const mixedNumber &x, const mixedNumber &y);
    friend
    mixedNumber operator*(const mixedNumber &x, const mixedNumber &y);
    friend
    mixedNumber operator/(const mixedNumber &x, const mixedNumber &y);

    friend
    bool operator<=(const mixedNumber &x, const mixedNumber &y);
    friend
    bool operator<(const mixedNumber &x, const mixedNumber &y);
    friend
    bool operator>(const mixedNumber &x, const mixedNumber &y);
    friend
    bool operator>=(const mixedNumber &x, const mixedNumber &y);
    friend
    bool operator==(const mixedNumber &x, const mixedNumber &y);
    friend
    bool operator!=(const mixedNumber &x, const mixedNumber &y);
};

#endif // MIXEDNUMBER_H
