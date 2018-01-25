#include <iostream>
#include <vector>

using namespace std;

struct Node {
        Node() {
                //nothing
        }
        Node(string name) {
                key = name;
        }       
        string key;
        vector<string> children;
        Node *next;
};

class Hash {
public:
        /* constructor */
        Hash();

        /* destructor */
        ~Hash();

        /* add student to course */
        void add(string parent, string child);

        /* Use hashfuction */
        int get_index(string key, int attempts);

        /* print set of nodes */
        void list();

        /* prints children of node */
        vector<string> children(string key);

        /* prints all paths between students */
        void paths(string start, string end);
        /* prints shortest path between students */
        void shortestpath(string start, string end);  

private:
        static const int INIT_CAPACITY = 10;

        /* table of nodes, hashed by name */
        Node *table;

        /* Number of courses in list */
        int size;

        /* Capacity of array */
        int capacity;

        /* Expand */
        void ensure_capacity(int desired);
};





