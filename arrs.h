#ifndef ARRS_H
#define ARRS_H

#include <arr.h>
#include <string>
#include <iostream>

using namespace std;

class Arrs
{
public:
    Arrs(int capacity=10);
    ~Arrs();

    void append(const Arr& var);
    void remove(int index);
    int getSize();

    Arr& operator[](int index);

private:
    int m_capacity;
    int m_size;
    Arr* m_address;

};

#endif // ARRS_H
