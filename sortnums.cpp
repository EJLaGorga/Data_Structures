#include <iostream>
#include <cstdlib>
#include <string.h>
#include <tgmath.h>
#include "Lists/IntVector.h"

using namespace std;

string algorithmFromCommandLine(string sort);
void   usageAbort (string progname, string message);
void   readNumbers(istream &input, IntVector &data);
void   sortNumbers(string algorithm, IntVector &data);
void   printNumbers(IntVector &data);

void bubbleSort(IntVector &data);
void swap(IntVector &vector, int i, int j);

void insertionSort(IntVector &data);

void mergeSort(IntVector &data);
IntVector merge(IntVector &left, IntVector &right);

void quickSort(IntVector &data, int left, int right);

void shellSort(IntVector &data);

void radixSort(IntVector &data);
int  findMax(IntVector &data);
int  digitSpan(int value);
int  sigDigit(int value, int index);


int main(int argc, char *argv[])
{
    (void) argc;
    IntVector data;
    string sortAlgorithm;

    sortAlgorithm = algorithmFromCommandLine((string)argv[1]);
    readNumbers(cin, data);
    sortNumbers(sortAlgorithm, data);
    printNumbers(data);

    return 0;
}


//Abort the program with a message on standard error
//explaining how to run the program correctly from the 
//command line.
void usageAbort(string progname, string message)
{
    cerr << message << endl
         << "Usage:  " << progname << " algorithm" << endl
         << "     where algorithm is one of "
         << "bubble, insertion, merge, quick, sort2 (shell), or sort3 (radix)"
         << endl;
    exit(1);
}

/***************************************************************************/
/**                      Functions you may want to write                  **/
/***************************************************************************/


//Return sorting algorithm specified on command line.
//Abort program if no algorithm is specified or if specified
//algorithm is not supported.
string algorithmFromCommandLine(string sort)
{
    if      (sort=="bubble")    return "bubble";
    else if (sort=="merge")     return "merge";
    else if (sort=="quick")     return "quick";
    else if (sort=="sort2")     return "shell";
    else if (sort=="insertion") return "insertion";
    else if (sort=="sort3")     return "radix";
    else usageAbort("./sortnums", "no valid sort provided");
    return "/n";
} 

//Read in a collection of integers from the given input stream
//and add them to the end of the data vector
void readNumbers(istream &input, IntVector &data)
{
    int val;
    while (input >> val)
        data.add(val);
}

//items are sorted using the chosen algorithm
void sortNumbers(string algorithm, IntVector &data)
{
    if (algorithm=="bubble")
        bubbleSort(data);
    if (algorithm=="merge")
        mergeSort(data);
    if (algorithm=="insertion")
        insertionSort(data);
    if (algorithm=="shell")
        shellSort(data);
    if (algorithm=="radix")
        radixSort(data);
    if (algorithm=="quick")
        quickSort(data, 0, data.get_size()-1);
}

//Print contents of data one item per line
void printNumbers(IntVector &data)
{
    for (int i=0; i < data.get_size(); i++) {
        cout << data[i] << endl;
    }
}

//Sort data with bubble sort
void bubbleSort(IntVector &data)
{
    //initialize truth condition
    bool swapped = true;

    //while last iteration not sorted
    while (swapped) {
        swapped = false;
        for (int i=1; i < data.get_size(); i++) {
            //if number to left is smaller swap
            if (data[i-1] > data[i]) {
                swap(data, i, i-1);
                swapped = true;
            }
        }
    }
}
 
//Swaps ints at position i and j in vector
void swap(IntVector &data, int i, int j)
{
    //save value at index i
    int temp = data[i];

    //set index i to value at index j
    data.set(i, data[j]);

    //set index j to saved value
    data.set(j, temp);
}

//Sort data with insertion sort
void insertionSort(IntVector &data)
{
    for (int i=1; i < data.get_size(); i++) {
        //compares value at index i with values to left
        for (int j=i; j > 0; j--) {
            //swaps if value at i is smaller
            if (data[j] < data[j-1])
                swap(data, j, j-1);
        }
    }
}

//Sort of contents of data using the merge sort algorithm
void mergeSort(IntVector &data)
{
    //base case: array has 1 element base
    if (data.get_size() <= 1)
        return;

    //split data into two sublists
    IntVector left;
    IntVector right;
    for (int i=0; i < data.get_size(); i++) {
        if (i % 2 == 0)
            left.add(data[i]);
        else
            right.add(data[i]);
    }

    //recurse seperation
    mergeSort(left);
    mergeSort(right);

    //update data with sorted array
    data = merge(left, right);
}

//merge two Intvectors together, maintaining order
IntVector merge(IntVector &left, IntVector &right)
{
    IntVector sorted;
    int L = 0;
    int R = 0;

    //while left and right are not empty
    while ((left.get_size()-L > 0) && (right.get_size()-R > 0)) {
        //add smallest number
        if (left[L] <= right[R]) {
            sorted.add(left[L]);
            L++;
        } else {
            sorted.add(right[R]);
            R++;
        }
    }

    //if one list is empty add rest of remaining list
    while (left.get_size()-L > 0) {
        sorted.add(left[L]);
        L++;
    }
    while (right.get_size()-R > 0) {
        sorted.add(right[R]);
        R++;
    }

    //return sorted array
    return sorted;
}

//Sort of contents of data using the quick sort algorithm
void quickSort(IntVector &data, int left, int right)
{
    //base case: subarray is sorted
    if (left >= right)
        return;

    //randomly innitialize pivot
    int pivot = data[(right + left) / 2];
    int L = left;
    int R = right;

    //while indexes have not crossed
    while (L <= R) {
        //move L right until swap needed
        while (data[L] < pivot)
            L++;
        //move R left until swap needed
        while (data[R] > pivot)
            R--;
        if (L <= R) {
            swap(data, L, R);
            L++;
            R--;
        }
    }

    //recursively sort smaller parts of array
    quickSort(data, left, R);
    quickSort(data, L, right);
}

//Sort of contents of data using the shell sort algorithm
void shellSort(IntVector &data)
{
    //get interval from Marcin Ciura's gap sequence
    int interval = 0;
    while ((interval * 3) + 1 < data.get_size())
        interval = (interval * 3) + 1;

    //until interval is 1
    while (interval > 0) {
        //iterate iterval start to end of data
        for (int i = interval; i < data.get_size(); i++) {
            
            /*for (int j=i; j >= interval; j -= interval) {
                if (data[j] < data[j-interval])
                    swap(data, j, j - interval);
            }*/
            //Can some explain why this works faster???

            int j;
            //save data at each index
            int temp = data[i];
            //insertion sort at indexs for interval starting at i
            for (j=i; (j >= interval) && (temp < data[j-interval]); j -= interval) {
                //switch values at j and interval space to left
                swap(data, j, j - interval);
            }
            data[j] = temp;

        }
        interval = (interval - 1) / 3;
    }
}

//Sort of contents of data using the radix sort algorithm
void radixSort(IntVector &data)
{
    //create empty Intvector for clearing numbers
    IntVector empty;
    //create 10 vectors for sorting by digits 0-9
    IntVector bucket[10];
    //get length of max number in data
    int digSpan = digitSpan(findMax(data));

    //for each digit in max loop through data
    for (int i=0; i < digSpan; i++) {
        //put data in buckets 0-9 by digit at place
        for (int j=0; j < data.get_size(); j++)
            bucket[sigDigit(data[j], i)].add(data[j]);
        //empty data
        data = empty;
        //replace numbers into Intvector after in order at place
        for (int k=0; k < 10; k++) {
            for (int l=0; l < bucket[k].get_size(); l++)
                data.add(bucket[k].get(l));
            //empty bucket
            bucket[k] = empty;
        }
    }
}

//return max value in data
int findMax(IntVector &data)
{
    int max = 0;
    for (int i=0; i < data.get_size(); i++){
        if (data[i] > max)
            max = data[i];
    }
    return max;
}

//return number of digits in value
int digitSpan(int value)
{ 
    int digSpan = 0;
    while(value > 0) {
        value /= 10;
        digSpan++;
    }
    return digSpan;
}

//return digit at index, no digit returns 0
int sigDigit(int value, int index)
{
    for (int i = 0; i < index; i++)
        value /= 10;

    int digit = value % 10;
    return digit;
}


