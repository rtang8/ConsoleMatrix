#include "smartarray.h"
#include <string>

/// CONSTRUCTORS - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
///
//smartArray::smartArray() {
//    list = NULL;
//    std::cout << "RUNNING DEFAULT SMARTARRAY CONSTRUCTOR" << std::endl;
//    try {
//        resize(5, true);
//    }
//    catch (smartArrayErrors e) {
//        if(e = OUT_OF_BOUNDS) {
//            std::cout << "OUT OF BOUNDS" << std::endl;
//        }
//        if(e = BAD_ARRAY_SIZE) {
//            std::cout << "BAD ARRAY SIZE" << std::endl;
//        }
//    }
//}

smartArray::smartArray(int size, bool zero) {
    // Points integer pointer to nothing
    list = NULL;

    //std::cout << "RUNNING SMARTARRAY CONSTRUCTOR" << std::endl;

    // Creates new array of size "size"
//  try {
        resize(size, zero);
//  }
//    catch (smartArrayErrors e) {
//        if(e = OUT_OF_BOUNDS) {
//            std::cout << "OUT OF BOUNDS" << std::endl;
//        }
//        if(e = BAD_ARRAY_SIZE) {
//            std::cout << "BAD ARRAY SIZE" << std::endl;
//        }
//    }
}

smartArray::~smartArray() {
    destroy();
}

smartArray::smartArray(const smartArray &other) {
    copy(other);
}

smartArray &smartArray::operator=(const smartArray &other) {
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
uint smartArray::size() const{
    return m_size;
}

void smartArray::zeroArray() {
    for(uint i = 0; i < m_size; ++i)
        list[i] = 0;
}

void smartArray::resize(int newSize, bool zero) {
    destroy();
    if(newSize < 1)
        throw BAD_ARRAY_SIZE;
    m_size = newSize;
    list = new (nothrow) mixedNumber[m_size];
    if(list == nullptr)
        throw BAD_ARRAY_SIZE;
    if(zero)
        zeroArray();
}

/// INDEX ACCESSORS - - - - - - - - - - - - - - - - - - - - - - - - - - - -
///
mixedNumber &smartArray::operator[](int index) {
    if(index < 0 || index > m_size)
        throw OUT_OF_BOUNDS;
    return list[index];
}

mixedNumber smartArray::operator[](int index) const {
    if(index < 0 || index > m_size)
        throw OUT_OF_BOUNDS;
    return list[index];
}

/// PRIVATE FUNCTIONS - - - - - - - - - - - - - - - - - - - - - - - - - - -
///
void smartArray::copy(const smartArray &other) {
    m_size = other.m_size;
    list = new (nothrow) mixedNumber[m_size];
    if(list == nullptr)
        throw BAD_ARRAY_SIZE;
    for(uint i = 0; i < m_size; ++i)
        list[i] = other.list[i];
}

void smartArray::destroy() {
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
std::ostream& operator<<(std::ostream &out,const smartArray &list) {
    if(&out != &cout)
        out << "Size: " << list.m_size << endl;

    // Outputs in format 'smartArray[0] = 0'
    for(uint i = 0; i < list.m_size; ++i)
        out << "smartArray[" << i << "] = " << list[i] << endl;

    return out;
}

std::istream& operator>>(std::istream &in, smartArray &list) {
    stringstream ss;
    string line;
    uint tempSize;

    // If file input, retrieve size and fill array
    if(&in == &cin) {
        in >> tempSize;
        list.resize(tempSize);
        for(uint i = 0; i < list.m_size; ++i) {
            cout << "smartArray[" << i << "] = ";
            in >> list[i];
        }
    }
    // File input will look like "Size: 5 \n smartArray[2] = 3"
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
