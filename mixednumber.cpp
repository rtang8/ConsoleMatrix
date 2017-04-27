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

    char ch;

    // Throws away leading whitespaces
    do {
        in.get(ch);
    } while(ch == ' ');

    // Booleans track existance of characters
    bool slash = false;
    bool underScore = false;
    bool dot = false;
    bool dash = false;
    std::string temp;
    std::stringstream toString;

    do {
          toString << ch;
          in.get(ch);
    } while (ch != '\n' && !in.eof());

    toString >> temp;

    if(&in == &std::cin && temp.length() > 10) {
        throw INPUT_TOO_LONG;
    }

    /// INPUT CHECKING - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // Scans for all the edge cases and throws errors
    for(uint i = 0; i < temp.length(); ++i) {
        if(!isdigit(temp[i]) && temp[i] != '.' && temp[i] != '_' && temp[i] != '/' && temp[i] != '-')
            throw HAS_ALPHABET;
        if(temp[i] == '.' && (dot || slash || underScore))
            throw IMPROPER_SYMBOL_USE;
        if(temp[i] == '.' && !dot)
            dot = true;

        if(temp[i] == '/' && (dot || slash))
            throw IMPROPER_SYMBOL_USE;
        if(temp[i] == '/' && !slash)
            slash = true;

        if(temp[i] == '_' && (dot || slash || underScore))
            throw IMPROPER_SYMBOL_USE;
        if(temp[i] == '_' && !underScore) {
            // Ensures there is a number before '_'
            if(i == 0)
                throw IMPROPER_SYMBOL_USE;
            underScore = true;
        }

        if(temp[i] == '-' && (dash || dot || slash || underScore))
            throw IMPROPER_SYMBOL_USE;
        if(temp[i] == '-' && !dash) {
            // Ensures - is the first character
            if(i != 0) {
                throw IMPROPER_SYMBOL_USE;
            }
            dash = true;
        }
    }

    // Ensures underscore is paired with slash
    if(underScore && !slash)
        throw IMPROPER_SYMBOL_USE;

    // Ensures something between underscore and slash
    if(underScore) {
        if(temp.find('/') - temp.find('_') == 1)
            throw IMPROPER_SYMBOL_USE;
    }
    // Ensures final character is a digit
    if(!isdigit(temp[temp.length() - 1]))
        throw IMPROPER_SYMBOL_USE;


    /// CONVERSIONS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    // Puts string into double
    if(dot) {
        double value;
        std::stringstream ss;
        ss << temp;
        ss >> value;
        x = Fraction(value);
        return in;
    }

    // Puts string into mixed number
    else if(underScore && slash) {

        size_t uSLoc = temp.find('_');
        size_t slLoc = temp.find('/');

        // Builds the whole part
        std::string insert = temp.substr(0, uSLoc);
        if(dash)
            insert = insert.substr(1);
        mixedNumber tempMix(atoi(insert.c_str()));

        // Builds fraction part
        insert = temp.substr(uSLoc + 1, (slLoc - uSLoc - 1));

        std::string insertTwo = temp.substr(slLoc + 1);
        Fraction part(atoi(insert.c_str()), atoi(insertTwo.c_str()));

        // Adds the two parts together
        x = tempMix + part;
        if(dash)
            x *= -1;
    }

    // Puts string into improper fraction
    else if(slash) {

        size_t slLoc = temp.find('/');

        // Builds fraction part
        std::string insert = temp.substr(0, slLoc);
        std::string insertTwo = temp.substr(slLoc + 1);

        mixedNumber finalIn(0, atoi(insert.c_str()), atoi(insertTwo.c_str()));
        x = finalIn;
    }
    else {
        x = mixedNumber(atoi(temp.c_str()));
    }

//    notFound = true;
//    while(isdigit(ch) || ((ch == '-') && notFound) || ch == '.') {
//        switch(ch) {
//            case '-' : notFound = false;
//                break;
//            case '.' : foundDecimal = true;
//        }
//        whole += ch;
//        if(!in.get(ch))
//            break;
//    }
//    if(foundDecimal) {
//        double value;
//        std::string temp;
//        std::stringstream ss;
//        ss << whole;
//        ss >> value;

//        //std::cout << "Value is " << value << std::endl;

//        x = Fraction(value);

//        return in;
//    }
//    if(ch == '_') {
//        if(isdigit(in.peek()) || in.peek() == '-') {
//            in >> part;
//            mixedNumber temp(part);
//            x = mixedNumber(atoi(whole.c_str())) + temp;
//            in.clear();
//            in.ignore(1000, '\n');
//            isWhole = true;
//        }
//    }
////    if(isalpha(ch) || (ispunct(ch) && ch != '/' && ch != '_')) {
////        if(isWhole) {
////            in.clear();
////            in.ignore(1000, '\n');
////        }
////        throw BAD_NUM_INPUT;
////    }
//    else {
//        if(ch == '/') {
//            for(int i = whole.size(); i > -1; --i) {
//                in.putback(whole[i]);
//            }
//            in >> part;
//            x = part;

//            if(x.m_whole != 0) {
//                Fraction tempFrac(x.toFraction());
//                mixedNumber temp(0, tempFrac.getNum(), tempFrac.getDenom());
//                x = temp;
//            }
//            in.clear();
//            in.ignore(1000, '\n');
//        }
//        else {
//            x = mixedNumber(atoi(whole.c_str()));
//        }
//    }

    return in;
}
