#include <iostream>
#include "hashtable.h"
#include "hashfunc.h"

using namespace std;

Hash::Hash()
{
    size = 0;
    capacity = INIT_CAPACITY;
    course = new Course[capacity];
} 

Hash::~Hash()
{
	delete[] course;
}

void Hash::instruct(string sn, string cn)
{
	//ensure class can be added
	ensure_capacity(size+1);

	int attempts = 0;	
	int index = get_index(cn, attempts);
	//find class in hash table, add if not included
	while (course[index].name != cn) {
		if (course[index].roster.empty()) {
			course[index].name = cn;
			size++;
		} 
		else index = get_index(cn, ++attempts);
	}
	//add students name to course roster
	course[index].roster.push_back(sn);
}

void Hash::enroll(string sn, string cn)
{
	//ensure class can be added
	ensure_capacity(size+1);

	int attempts = 0;	
	int index = get_index(cn, attempts);
	//find class in hash table, add if not included
	while (course[index].name != cn) {
		if (course[index].roster.empty()) {
			course[index].name = cn;
			size++;
		} 
		else index = get_index(cn, ++attempts);
	}
	//add students name to course roster
	course[index].roster.push_back(sn);
}

void Hash::ensure_capacity(int desired)
{
	//check if desired capacity available
	if (capacity >= desired)
		return;
	else {
		//double capacity
		capacity = desired*2;
		//create new course array
		Course *temp = new Course[capacity];
		//rehash old classes into new table
		for (int i=0; i < size; i++) {
			int attempts = 0;
			int index = get_index(course[i].name, attempts);
			while (!temp[index].roster.empty())
				index = get_index(course[i].name, ++attempts);
			temp[index] = course[i];
		}
		//delete old array
		delete[] course;
		//point course to temp
		course = temp;
	}
}

int Hash::get_index(string key, int attempts)
{
	uint32_t value = hash_string(key);
	uint32_t index = (value + attempts) % capacity;
	return (int) index;
}

void Hash::lc()
{
    vector<string>::iterator it;
    for (it=names.begin(); it != names.end(); it++)
        cout << *it << endl;
}

void Hash::lc()
{
	for (int i=0; i < capacity; i++) {
		if (!course[i].roster.empty())
			cout << course[i].name << endl;
	}
}









