#ifndef SMARTDOUBLEARRAY_H
#define SMARTDOUBLEARRAY_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "smartarray.h"

using namespace std;


class smartDoubleArray {

private:
    double *list;
    uint m_size;

    void copy(const smartDoubleArray &other);
    void destroy();

public:
    //smartDoubleArray();
    smartDoubleArray(int size = 5, bool zero = true);
    ~smartDoubleArray();
    smartDoubleArray(const smartDoubleArray &other);
    smartDoubleArray &operator=(const smartDoubleArray &other);

    uint size() const;
    void zeroArray();

    void resize(int newSize, bool zero = true);

    double &operator[](int index);
    double  operator[](int index) const;

    friend
    ostream& operator<<(ostream &out,const smartDoubleArray &list);

    friend
    istream& operator>>(istream &in, smartDoubleArray &list);

};


#endif // SMARTDOUBLEARRAY_H
