/*
 * A replacement for (integer) arrays that lets you say dynamically
 * how big the array should be.
 *
 * Mark A. Sheldon, Tufts University
 * Spring 2013
 *
 */

class IntVector
{
public:
        IntVector();

        /*
         * A constructor with an initial size is optional.
         */
        IntVector(int initialSize);

        IntVector(const IntVector &source);
        IntVector &operator=(const IntVector &rhs);

        ~IntVector();

        /*
         * Makes the vector have a size and capacity of 0 and 
         * recycles heap-allocated storage.
         */
        void destroy();

        /*
         * Return integer value at given index.
         *
         * Throw exception or abort with error message if index 
         * out of range.
         */
        int get(int index) const;

        /*
         * Set array element at given index to newVal.
         *
         * Throw exception or abort with error message if index 
         * out of range.
         */
        void set(int index, int newVal);

        /*
         * Return reference to array slot at given index.
         * This permits subscripted access to vector as 
         * L-value and/or R-value.
         *
         * Throw exception or abort with error message if index 
         * out of range.
         */
        int  &operator[](int index) const;

        /* Add newVal to end of vector, increasing current size by one. */
        void add(int newVal);

        /* Return current size of vector. */
        int get_size() const;

        /* Return current capacity of vector */
        int get_capacity() const;

private:
        /* Dynamic array */
        int *array;

        /* Number of elements in array */
        int size;
        /* Capacity of array */
        int capacity;

        /* Enlarges array, maintaining data */
        void expand();
        /* Prints error, show how to run */
        void usageAbort(int index) const;
};






