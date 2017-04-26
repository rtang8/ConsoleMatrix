#include "mixednumber.h"

/// CONSTRUCTORS
///
mixedNumber::mixedNumber() {
    m_whole = 0;
}

mixedNumber::~mixedNumber() {}


mixedNumber::mixedNumber(double value) {
    m_whole = 0;
    m_frac = Fraction(value);
}

mixedNumber::mixedNumber(int whole, int num, int denom) {
    m_whole = whole;
    m_frac = Fraction(num, denom);
}

mixedNumber::mixedNumber(const mixedNumber& other) {
    copy(other);
}

mixedNumber::mixedNumber(const Fraction &other) {
    m_whole = other.getNum() / other.getDenom();
    if(m_whole == 0)
        m_frac = other;
    else {
        int temp = abs(other.getNum()) - abs(m_whole)*other.getDenom();
        m_frac = Fraction(temp, other.getDenom());
    }
}

/// PRIVATE FUNCTIONS
///
void mixedNumber::copy(const mixedNumber& other) {
    m_whole = other.m_whole;
    m_frac = other.m_frac;
}

int mixedNumber::gcd(int p, int q) const{
    return q == 0 ? p : gcd(q, p % q);
}

/// PUBLIC FUNCTIONS
///
Fraction mixedNumber::toFraction() const{
    if(m_frac.getValue() == 0) {
        int num = m_frac.getDenom() * m_whole + m_frac.getNum();
        int denom = m_frac.getDenom();
        return Fraction(num, denom);
    }
    else {
        const long PERCISION = 1000000000;
        double whole = std::floor(m_frac.getValue());
        double frac = m_frac.getValue() - whole;
        int gcdenom = gcd(round(frac * PERCISION), PERCISION);
        long den = PERCISION / gcdenom;
        long num = round(frac * PERCISION) / gcdenom;
        return Fraction((num+(den*whole)), den);
    }
}

int mixedNumber::getWhole() const {
    return m_whole;
}

Fraction mixedNumber::getFrac() const {
    return m_frac;
}

/// COPY
///
mixedNumber &mixedNumber::operator=(const mixedNumber &other) {
    if(this != &other) {
        copy(other);
    }
    return *this;
}

/// MATH OPERATORS
///
mixedNumber &mixedNumber::operator+=(const mixedNumber &other) {
    *this = *this + other;
    return *this;
}

mixedNumber &mixedNumber::operator-=(const mixedNumber &other) {
    *this = *this - other;
    return *this;
}

mixedNumber &mixedNumber::operator*=(const mixedNumber &other) {
    *this = *this * other;
    return *this;
}

mixedNumber &mixedNumber::operator/=(const mixedNumber &other) {
    *this = *this / other;
    return *this;
}

mixedNumber operator+(const mixedNumber &x, const mixedNumber &y) {
    Fraction fracX = x.toFraction();
    Fraction fracY = y.toFraction();
    Fraction fracZ(fracX + fracY);
    return mixedNumber(fracZ);
}

mixedNumber operator-(const mixedNumber &x, const mixedNumber &y) {
    Fraction fracX = x.toFraction();
    Fraction fracY = y.toFraction();
    Fraction fracZ = fracX - fracY;
    return mixedNumber(fracZ);
}

mixedNumber operator*(const mixedNumber &x, const mixedNumber &y) {
    Fraction fracX = x.toFraction();
    Fraction fracY = y.toFraction();
    Fraction fracZ = fracX * fracY;
    return mixedNumber(fracZ);
}

mixedNumber operator/(const mixedNumber &x, const mixedNumber &y) {
    Fraction fracX = x.toFraction();
    Fraction fracY = y.toFraction();
    Fraction fracZ = fracX / fracY;
    return mixedNumber(fracZ);
}

/// COMPARISON OPERATORS
bool operator<=(const mixedNumber &x, const mixedNumber &y) {
    Fraction fracX = x.toFraction();
    Fraction fracY = y.toFraction();
    return fracX <= fracY;
}

bool operator<(const mixedNumber &x, const mixedNumber &y) {
    Fraction fracX = x.toFraction();
    Fraction fracY = y.toFraction();
    return fracX < fracY;
}

bool operator>(const mixedNumber &x, const mixedNumber &y) {
    Fraction fracX = x.toFraction();
    Fraction fracY = y.toFraction();
    return fracX > fracY;
}

bool operator>=(const mixedNumber &x, const mixedNumber &y) {
    Fraction fracX = x.toFraction();
    Fraction fracY = y.toFraction();
    return fracX >= fracY;
}

bool operator==(const mixedNumber &x, const mixedNumber &y) {
    Fraction fracX = x.toFraction();
    Fraction fracY = y.toFraction();
    return fracX == fracY;
}

bool operator!=(const mixedNumber &x, const mixedNumber &y) {
    Fraction fracX = x.toFraction();
    Fraction fracY = y.toFraction();
    return fracX != fracY;
}

/// I/O OPERATORS
///
std::ostream &operator<<(std::ostream &out, const mixedNumber &x) {

    //std::cout << "Value of x : " << x.m_frac.getValue() << std::endl;
    if(x.m_frac == 0 && x.m_frac.getValue() == 0.0)
        out << x.m_whole;
    else {
        if(x.m_whole == 0)
            out << x.m_frac;
        else
            out << x.m_whole << '_' << x.m_frac;
    }
    return out;
}

std::istream &operator>>(std::istream &in, mixedNumber &x) {
    std::string whole;
    Fraction part;
    bool notFound, foundDecimal = false;
    bool isWhole = false;
    char ch;

    int counter = 0;

    do {
        in.get(ch);
        ++counter;
    }
    while(ch == ' ');

    if(counter > 10) {
        throw INPUT_TOO_LONG;
    }

    notFound = true;
    while(isdigit(ch) || ((ch == '-') && notFound) || ch == '.') {
        switch(ch) {
            case '-' : notFound = false;
                break;
            case '.' : foundDecimal = true;
        }
        whole += ch;
        if(!in.get(ch))
            break;
    }
    if(foundDecimal) {
        double value;
        std::string temp;
        std::stringstream ss;
        ss << whole;
        ss >> value;

        //std::cout << "Value is " << value << std::endl;

        x = Fraction(value);

        return in;
    }
    if(ch == '_') {
        if(isdigit(in.peek()) || in.peek() == '-') {
            in >> part;
            mixedNumber temp(part);
            x = mixedNumber(atoi(whole.c_str())) + temp;
            in.clear();
            in.ignore(1000, '\n');
            isWhole = true;
        }
    }
//    if(isalpha(ch) || (ispunct(ch) && ch != '/' && ch != '_')) {
//        if(isWhole) {
//            in.clear();
//            in.ignore(1000, '\n');
//        }
//        throw BAD_NUM_INPUT;
//    }
    else {
        if(ch == '/') {
            for(int i = whole.size(); i > -1; --i) {
                in.putback(whole[i]);
            }
            in >> part;
            x = part;

            if(x.m_whole != 0) {
                Fraction tempFrac(x.toFraction());
                mixedNumber temp(0, tempFrac.getNum(), tempFrac.getDenom());
                x = temp;
            }
            in.clear();
            in.ignore(1000, '\n');
        }
        else {
            x = mixedNumber(atoi(whole.c_str()));
        }
    }

    return in;
}
