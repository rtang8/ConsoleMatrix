#include "fraction.h"

/// CONSTRUCTORS
///
Fraction::Fraction() {
    m_num = 0;
    m_denom = 1;
    m_value = 0;
}

Fraction::~Fraction() {}

Fraction::Fraction(int num, int denom) {
    m_num = num;
    m_denom = denom;
    m_value = 0;
    reduce();
}

Fraction::Fraction(double value) {
    m_value = value;
    m_denom = 1;
    m_num = 0;
}

Fraction::Fraction(const Fraction &other) {
    copy(other);
}
/// MEMBER ACCESSORS
///
int Fraction::getDenom() const {
    return m_denom;
}

int Fraction::getNum() const {
    return m_num;
}

double Fraction::getValue() const {
    return m_value;
}

/// PRIVATE FUNCTIONS
///
int Fraction::gcd(int p, int q) {
    return q == 0 ? p : gcd(q, p % q);
}

void Fraction::reduce() {
    int div = gcd(m_num, m_denom);
    m_num /= div;
    m_denom /= div;
    if(m_denom < 0) {
        m_num *= -1;
        m_denom *= -1;
    }
}

void Fraction::copy(const Fraction &other) {
    m_num = other.m_num;
    m_denom = other.m_denom;
    m_value = other.m_value;
}

/// COPY
///
Fraction &Fraction::operator=(const Fraction &other) {
    if(this != &other)
        copy(other);
    return *this;
}

/// MATH OPERATORS
///
Fraction &Fraction::operator+=(const Fraction &other) {
    *this = *this + other;
    return *this;
}

Fraction &Fraction::operator-=(const Fraction &other) {
    *this = *this - other;
    return *this;
}

Fraction &Fraction::operator*=(const Fraction &other) {
    *this = *this * other;
    return *this;
}

Fraction &Fraction::operator/=(const Fraction &other) {
    *this = *this / other;
    return *this;
}

Fraction operator+(const Fraction &x, const Fraction &y) {
    int num = x.m_num * y.m_denom + y.m_num * x.m_denom;
    int denom = x.m_denom * y.m_denom;
    Fraction ans(num, denom);
    return ans;
}

Fraction operator-(const Fraction &x, const Fraction &y) {
    int num = x.m_num * y.m_denom - y.m_num * x.m_denom;
    int denom = x.m_denom * y.m_denom;
    Fraction ans(num, denom);
    return ans;
}

Fraction operator*(const Fraction &x, const Fraction &y) {
    int num = x.m_num * y.m_num;
    int denom = x.m_denom * y.m_denom;
    Fraction ans(num, denom);
    return ans;
}

Fraction operator/(const Fraction &x, const Fraction &y) {
    int num = x.m_num * y.m_denom;
    int denom = x.m_denom * y.m_num;
    Fraction ans(num, denom);
    return ans;
}

/// COMPARISON OPERATORS
///
bool operator<=(const Fraction &x, const Fraction &y) {
    return !(x > y);
}

bool operator<(const Fraction &x, const Fraction &y) {
    return !(x >= y);
}

bool operator>=(const Fraction &x, const Fraction &y) {
    return x.m_num * y.m_denom >= x.m_denom * y.m_num;
}

bool operator>(const Fraction &x, const Fraction &y) {
    return x.m_num * y.m_denom > x.m_denom * y.m_num;
}

bool operator==(const Fraction &x, const Fraction &y) {
    return x.m_num * y.m_denom == x.m_denom * y.m_num;
}

bool operator!=(const Fraction &x, const Fraction &y) {
    return !(x == y);
}

/// IO OPERATORS
///
std::ostream &operator<<(std::ostream &out, const Fraction &x) {
    if(x.m_value != 0)
        out << x.m_value;
    else
        out << x.m_num << "/" << x.m_denom;
    return out;
}

std::istream &operator>>(std::istream &in, Fraction &x) {
    char junk;
    in >> x.m_num >> junk >> x.m_denom;
    x.reduce();
    return in;
}
