#ifndef FRACTION_H
#define FRACTION_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>

class Fraction {
private:
    int m_num, m_denom;
    double m_value;
    void reduce();
    void copy(const Fraction &other);
    int gcd(int p, int q);

public:
    Fraction();
    ~Fraction();
    Fraction(int num, int denom = 1);
    Fraction(double value);
    Fraction(const Fraction &other);


    int getDenom() const;
    int getNum() const;
    double getValue() const;

    Fraction &operator=(const Fraction &other);
    Fraction &operator+=(const Fraction &other);
    Fraction &operator-=(const Fraction &other);
    Fraction &operator*=(const Fraction &other);
    Fraction &operator/=(const Fraction &other);

    friend
    std::ostream &operator<<(std::ostream &out, const Fraction &x);
    friend
    std::istream &operator>>(std::istream &in, Fraction &x);

    friend
    Fraction operator+(const Fraction &x, const Fraction &y);
    friend
    Fraction operator-(const Fraction &x, const Fraction &y);
    friend
    Fraction operator*(const Fraction &x, const Fraction &y);
    friend
    Fraction operator/(const Fraction &x, const Fraction &y);

    friend
    bool operator<=(const Fraction &x, const Fraction &y);
    friend
    bool operator<(const Fraction &x, const Fraction &y);
    friend
    bool operator>=(const Fraction &x, const Fraction &y);
    friend
    bool operator>(const Fraction &x, const Fraction &y);
    friend
    bool operator==(const Fraction &x, const Fraction &y);
    friend
    bool operator!=(const Fraction &x, const Fraction &y);

};

#endif // FRACTION_H
