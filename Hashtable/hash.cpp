#include <iostream>
#include "hash.h"
#include "hashfunc.h"

using namespace std;

Hash::Hash()
{
    size = 0;
    capacity = INIT_CAPACITY;
    table = new Node[capacity];
} 

Hash::~Hash()
{
	delete[] table;
}

void Hash::add(string parent, string child)
{
	//ensure class can be added
	ensure_capacity(size+1);

	int attempts = 0;	
	int index = get_index(parent, attempts);
	//find class in hash table, add if not included
	while (table[index].key != parent) {
		if (table[index].children.empty()) {
			table[index].key = parent;
			size++;
		} 
		else index = get_index(parent, ++attempts);
	}
	//add students name to course roster
	table[index].children.push_back(child);
}

void Hash::mark(string name)
{
	//ensure class can be added
	ensure_capacity(size+1);

	int attempts = 0;	
	int index = get_index(name, attempts);
	//find class in hash table, add if not included
	while (table[index].key != name) {
		if (table[index].key == "")
			table[index].key = name;
			size++;
		} 
		else index = get_index(name, ++attempts);
	}
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
		Node *temp = new Node[capacity];
		//rehash old classes into new table
		for (int i=0; i < size; i++) {
			int attempts = 0;
			int index = get_index(table[i].key, attempts);
			while (!temp[index].children.empty())
				index = get_index(table[i].key, ++attempts);
			temp[index] = table[i];
		}
		//delete old array
		delete[] table;
		//point course to temp
		table = temp;
	}
}

int Hash::get_index(string key, int attempts)
{
	uint32_t value = hash_string(key);
	uint32_t index = (value + attempts) % capacity;
	return (int) index;
}

void Hash::list()
{
	for (int i=0; i < capacity; i++) {
		if (!table[i].children.empty())
			cout << table[i].key << endl;
	}
}

vector<string> Hash::children(string name)
{
	int attempts = 0;
	int index = get_index(name, attempts);
	while (table[index].key != name)
		index = get_index(name, ++attempts);

	return table[index].children;
}







