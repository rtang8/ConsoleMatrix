#ifndef SMARTARRAY_H
#define SMARTARRAY_H

#include "mixednumber.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

typedef unsigned int uint;
using namespace std;

enum smartArrayErrors {BAD_ARRAY_SIZE, OUT_OF_BOUNDS};

class smartArray {

private:
    mixedNumber *list;
    uint m_size;

    void copy(const smartArray &other);
    void destroy();

public:
    //smartArray();
    smartArray(int size = 5, bool zero = true);
    ~smartArray();
    smartArray(const smartArray &other);
    smartArray &operator=(const smartArray &other);

    uint size() const;
    void zeroArray();

    void resize(int newSize, bool zero = true);

    mixedNumber &operator[](int index);
    mixedNumber  operator[](int index) const;

    friend
    ostream& operator<<(ostream &out,const smartArray &list);

    friend
    istream& operator>>(istream &in, smartArray &list);

};

#endif // SMARTARRAY_H
