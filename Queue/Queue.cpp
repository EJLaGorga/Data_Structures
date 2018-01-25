/*
 * Queue.cpp
 *
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include "Queue.h"
#include "Student.h"

using namespace std;

// constructor
Queue::Queue()
{
		capacity = QUEUE_INIT_CAPACITY;
		queue_array = new Student[QUEUE_INIT_CAPACITY];
		size = 0;
		front = 0;
		back = 0;
}

// destructor
Queue::~Queue()
{
		delete[] queue_array;
}

// enqueue a student onto at the back of the queue
void Queue::enqueue(const Student &s)
{
		//ensure capacity
		ensure_capacity(size+1);

		//insert student in queue array at back
		queue_array[back] = s;

		//move back to next index
		back = (back+1)%capacity;

		//increment size
		size++;
}

// dequeue a student from the front of the queue
Student Queue::dequeue()
{
		//throw an exception if empty
		if (is_empty()){
				cout << "Queue empty when dequeued, " << crash() << endl;
    	}
	
		//copy student at front
		Student temp_student = queue_array[front];

		//delete student at front
		front = (front+1)%capacity;

		//decrement size
		size--;

		//return deleted student
		return temp_student;
}

// throws an error
int Queue::crash()
{
    	throw runtime_error("Crashing!");
}

// returns true if there are no elements in the
// queue, false if the queue has elements
bool Queue::is_empty()
{
		//checks if size is 0
		return (size == 0);
}

// Make sure the circular array has at least the requested 
//capacity, if it doesn't already, expand the capacity
void Queue::ensure_capacity(int desiredCapacity)
{
		//check if desired capacity available
		if (capacity >= desiredCapacity) {
				return;
		} else { 
				//create new array
				Student *temp_array = new Student[desiredCapacity*2];
				//copy old array to temp array
				for (int i=0; i < size; i++){
						temp_array[i] = queue_array[(front+i)%capacity];
				}
				//delete old array
				delete[] queue_array;
				//reset values
				queue_array = temp_array;
				front = 0;
				back = size;
				capacity = desiredCapacity*2;
		}
}





