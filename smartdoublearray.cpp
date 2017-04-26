#include "smartarray.h"
#include "smartdoublearray.h"
#include <string>

/// CONSTRUCTORS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
///

smartDoubleArray::smartDoubleArray(int size, bool zero) {
    // Points integer pointer to nothing
    list = NULL;
    resize(size, zero);
}

smartDoubleArray::~smartDoubleArray() {
    destroy();
}

smartDoubleArray::smartDoubleArray(const smartDoubleArray &other) {
    copy(other);
}

smartDoubleArray &smartDoubleArray::operator=(const smartDoubleArray &other) {
    if(this != &other) {
        if(m_size == other.m_size) {
            for(uint i = 0; i < m_size; ++i)
                list[i] = other.list[i];
        }
        else {
            destroy();
            copy(other);
        }
    }
    return *this;
}

/// GENERAL FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - -
///
uint smartDoubleArray::size() const{
    return m_size;
}

void smartDoubleArray::zeroArray() {
    for(uint i = 0; i < m_size; ++i)
        list[i] = 0;
}

void smartDoubleArray::resize(int newSize, bool zero) {
    destroy();
    if(newSize < 1)
        throw BAD_ARRAY_SIZE;
    m_size = newSize;
    list = new (nothrow) double[m_size];
    if(list == nullptr)
        throw BAD_ARRAY_SIZE;
    if(zero)
        zeroArray();
}

/// INDEX ACCESSORS - - - - - - - - - - - - - - - - - - - - - - - - - - - -
///
double &smartDoubleArray::operator[](int index) {
    if(index < 0 || index > m_size)
        throw OUT_OF_BOUNDS;
    return list[index];
}

double smartDoubleArray::operator[](int index) const {
    if(index < 0 || index > m_size)
        throw OUT_OF_BOUNDS;
    return list[index];
}

/// PRIVATE FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - -
///
void smartDoubleArray::copy(const smartDoubleArray &other) {
    m_size = other.m_size;
    list = new (nothrow) double[m_size];
    if(list == nullptr)
        throw BAD_ARRAY_SIZE;
    for(uint i = 0; i < m_size; ++i)
        list[i] = other.list[i];
}

void smartDoubleArray::destroy() {
    // Quits function if list does not yet exist
    if(!list)
        return;

    // Resets array and deletes previous information
    zeroArray();
    delete[] list;
    m_size = 0;
    list = NULL;
}

/// FRIEND I/O OPERATORS - - - - - - - - - - - - - - - - - - - - - - - - -
///
std::ostream& operator<<(std::ostream &out,const smartDoubleArray &list) {
    if(&out != &cout)
        out << "Size: " << list.m_size << endl;

    // Outputs in format 'smartDoubleArray[0] = 0'
    for(uint i = 0; i < list.m_size; ++i)
        out << "smartDoubleArray[" << i << "] = " << list[i] << endl;

    return out;
}

std::istream& operator>>(std::istream &in, smartDoubleArray &list) {
    stringstream ss;
    string line;
    uint tempSize;

    // If file input, retrieve size and fill array
    if(&in == &cin) {
        in >> tempSize;
        list.resize(tempSize);
        for(uint i = 0; i < list.m_size; ++i) {
            cout << "smartDoubleArray[" << i << "] = ";
            in >> list[i];
        }
    }
    // File input will look like "Size: 5 \n smartDoubleArray[2] = 3"
    else {
        getline(in, line);
        ss << line.substr(6);
        ss >> list.m_size;
        for(uint i = 0; i < list.m_size; ++i) {
            getline(in, line);
            uint pos = line.find('=');
            ss << line.substr(pos+1);
            ss >> list[i];
        }
    }
}
