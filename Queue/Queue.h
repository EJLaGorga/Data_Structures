/*
 * Queue.h
 *
 * This is the header for a Queue with the following methods:
 * void enqueue(Student c);
 * Student dequeue();
 * bool is_empty();
 *
 * You may add private members to this class, but you cannot change
 * the public section.
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include "Student.h"

class Queue {
public:
        // constructor
        Queue();

        // destructor
        ~Queue();

        // enqueue a student onto at the back of the queue
        void enqueue(const Student &s);

        // dequeue a student from the front of the queue
        Student dequeue();

        // returns true if there are no elements in the
        // queue, false if the queue has elements
        bool is_empty();

private:
        static const int QUEUE_INIT_CAPACITY = 2;

        Student *queue_array;  // the dynamic array for the queue
        int      capacity;     // the capacity of the queue 
        int      size;         // how many characters there are in the queue
        int      front;        // the front of the queue
        int      back;         // the back of the queue
        int      crash();      // throws an exception
        void     ensure_capacity(int desiredCapacity);     // expand the circular queue
};

#endif /* QUEUE_H_ */
