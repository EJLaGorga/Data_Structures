#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

struct Course {
        Course() {
                //nothing
        }
        Course(string cn) {
                name = cn;
        }       
        string key;
        vector<string> roster;
        Course *next;
};

struct Student {
        string name;
        vector<string> course;
};

/*struct Student {
        Student() {
                //nothing
        }
        Student(string sn) {
                name = sn;
                TAed = NULL;
        }        
        ~Student() {
                Course *current = TAed;
                while (current != NULL) {
                        Course *temp = current->next;
                        delete current;
                        current = temp;
                }
        }
        string name;
        Course *TAed;
};*/

class Hash {
public:
        /* constructor */
        Hash();

        /* destructor */
        ~Hash();

        /* add student to course */
        void enroll(string sn, string cn);

        /* print set of students */
        void ls();
        /* print set of courses */
        void lc();
        /* prints classes at student taed */
        void taed(string sn);
        /* prints students in a class */
        void roster(string cn);
        /* prints all paths between students */
        void paths(string start, string end);
        /* prints shortest path between students */
        void shortestpath(string start, string end);  

private:
        static const int INIT_CAPACITY = 3;

        /* set of students */
        unordered_set<string> students;

        /* table of courses, hashed by name */
        Course *course;
        /* Number of courses in list */
        int size;
        /* Capacity of array */
        int capacity;
        /* Expand */
        void ensure_capacity(int desired);

        /* Use hashfuction */
        int get_index(string key, int attempts);
};