/*
 * Set.cpp
 *
 * Add your code below.  Do not change the print function.
 *
 */

#include <iostream>
#include "Set.h"

using namespace std;

// Constructor
Set::Set()
{
		capacity = SET_INIT_CAPACITY;
		set_array = new Student[SET_INIT_CAPACITY];
		enrollment = 0;
}

// Destructor
Set::~Set()
{
		delete[] set_array;
}

// Adds student to class if they aren't already
// Returns true if added, false otherwise
bool Set::add(Student s)
{
		//checks if student is enrolled
		if (is_enrolled(s))
				return false;

		//ensure capacity, otherwise expand
		ensure_capacity(enrollment+1);

		//adds student to class
		set_array[enrollment] = s;
	
		//increment enrollment
		enrollment++;
	
		return true;
}

// Removes student from class
// Returns true if removed, false otherwise
bool Set::drop(Student s)
{
		//checks if student is not enrolled
		if (!is_enrolled(s))
				return false;

		//iterates through set_array to find index of student
		int index = 0;
		for (int i=0; i < enrollment; i++){
				if (set_array[i].name == s.name)
						index = i;
		}

		//decrement enrollment
		enrollment--;

		//removes student from set_array
		for (int j=index; j < enrollment; j++){
				set_array[j] = set_array[j+1];
		}

		return true;
}

// Iterates through array of students
// Returns true if student found, false otherwise
bool Set::is_enrolled(Student s)
{
		//iterates through set_array to see if it contains student
		for (int i=0; i < enrollment; i++){
				if (set_array[i].name == s.name)
						return true;
		}

		return false;
}

// Returns class enrollment
int Set::size()
{
		return enrollment;
}

// Make sure the array has at least the requested capacity
// If it doesn't already, expand the capacity
void Set::ensure_capacity(int desiredCapacity)
{
		//check if desired capacity available
		if (capacity > desiredCapacity)
				return;

		//create new array
		Student *temp_array = new Student[desiredCapacity*2];
		//copy new array into old array
		for (int i=0; i < enrollment; i++){
				temp_array[i] = set_array[i];
		}
		//delete old array
		delete[] set_array;
		//reset values
		set_array = temp_array;
		capacity = desiredCapacity*2;
}

void Set::print_class()
{
    	for (int i = 0; i < enrollment; i++) {
        	Student s = set_array[i];
        	cout << s.name << ", "
            		<< (s.major ? "Major" : "Non-Major")
            		<< "\n";
    	}
}
