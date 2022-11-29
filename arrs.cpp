#include "arrs.h"


Arrs::Arrs(int capacity)
{
    m_capacity = capacity;
    m_size = 0;
    m_address = new Arr[m_capacity];
}

Arrs::~Arrs()
{
    if (m_address != nullptr)
    {
        delete [] m_address;
        m_address = nullptr;
    }
}


void Arrs::append(const Arr& var)
{
    if (m_capacity == m_size)
    {
        m_capacity *= 2;
        Arr* new_list = new Arr[m_capacity];
        for (int i = 0; i < m_size; i++)
        {
            new_list[i] = m_address[i];
        }
        delete [] m_address;
        m_address = new_list;
        m_address[m_size] = var;
        m_size++;
    }
    else
    {
        m_address[m_size] = var;
        m_size++;
    }
}

void Arrs::remove(int index)
{
    for (int i = index; i < m_size; i++)
    {
        *(m_address + i) = *(m_address + i + 1);
    }
    m_size--;
}

int Arrs::getSize()
{
    return m_size;
}

Arr& Arrs::operator[](int index)
{
    if (index > m_size - 1 || index < 0)
    {
        exit(20);
    }
    return m_address[index];
}
