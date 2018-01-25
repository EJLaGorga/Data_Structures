#include <stdio.h>      
#include <stdlib.h>  
#include <iostream>
#include "IntVector.h"

using namespace std;

IntVector::IntVector()
{
    size = 0;
    capacity = 0;
    array = new int[capacity];
}

IntVector::~IntVector()
{
    destroy();
}

IntVector::IntVector(int initialSize)
{
	size = 0;
    capacity = initialSize;
    array = new int[capacity];
}

IntVector::IntVector(const IntVector &source)
{
    //copy 
    size = source.get_size();
    capacity = source.get_capacity();
    //deep copy dynamic array
    array = new int[capacity];
    for (int i=0; i < size; i++)
        array[i] = source.array[i]; 
}

IntVector &IntVector::operator=(const IntVector &rhs)
{
    //check for alias
    if (this != &rhs) {
        //copy
        size = rhs.size;
        capacity = rhs.capacity;
        for (int i=0; i < size; i++)
            array[i] = rhs.array[i];    
    }
    //return self
    return *this;
}

void IntVector::destroy()
{
    size = 0;
    capacity = 0;
    // delete heap allocated memory
    delete[] array;
}

int IntVector::get(int index) const
{
    if ((index > size) || (index < 0))
        usageAbort(index);
    
    return array[index];
}

void IntVector::set(int index, int newVal)
{
	if ((index > size) || (index < 0))
        usageAbort(index);
    
    array[index] = newVal;
}

int &IntVector::operator[](int index) const
{
    if ((index > size) || (index < 0))
        usageAbort(index);

    return array[index];
}

void IntVector::add(int newVal)
{
	if (size >= capacity)
    	expand();

    array[size] = newVal;
    size++;
}

int IntVector::get_size() const
{
    return size;
}

int IntVector::get_capacity() const
{
    return capacity;
}

void IntVector::expand()
{
    int *temp = new int[(capacity * 2) + 1];
    for (int i=0; i < size; i++)
        temp[i] = array[i];
    delete[] array;
    array = temp;
    capacity = (capacity * 2) + 1;
}

void IntVector::usageAbort(int index) const
{
    cerr << "Index: " << index << " is outside of "
    << "vector range" << endl
    << "Usage: ./sortnums algorithm" << endl
    << "     where algorithm is one of "
    << "bubble, insertion, merge, quick, shell, or radix"
    << endl;
    exit(1);
}

