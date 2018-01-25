// List_dynamic_array.h
// The List_dynamic_array header

// Purpose:  Create a list using a dynamic array that grows as needed.
//           The list is comprised of an array of Cards, which can be
//           inserted, removed, and replaced in a number of different
//           ways.
//
//           The "front" of the list is at the beginning of the array
//           The "back"  of the list is at the end of the array


#ifndef List_dynamic_array_h
#define List_dynamic_array_h

#include "card.h"

class List_dynamic_array
{
public:
	List_dynamic_array();
	~List_dynamic_array();

	// Need to define/overload copy constructor and assignment operator
	List_dynamic_array(const List_dynamic_array& source);
	List_dynamic_array operator =(const List_dynamic_array& source);

        // prints the list in human-readable form
	void print_list();

        // prints the list as integers based on rank and suit
	void print_list_int();

        // returns true if list has no elements, false otherwise
	bool is_empty();

        // makes the list empty (very cheap)
	void make_empty();
	 
        // insert new card at the beginning/end of the list or at given index
	void insert_at_front(Card c);
	void insert_at_back(Card c);
	void insert_at_index(Card c, int index);

        // replaces card at given index
	void replace_at_index(Card c, int index);

        // return card at given index
	Card card_at(int index);
	
        // return true if the card is in the list, false otherwise
	bool has_card(Card c);
	
        // remove given card
	bool remove(Card c); 

        // removes first/last card or card at given index
	Card remove_from_front();
	Card remove_from_back();
	Card remove_from_index(int index);
	
        // return number of cards current in the list
	int cards_in_hand();
	
private:
        static const int INITIAL_CAPACITY = 10;   // initial size of our list.
	void expand();                            // expand list when necessary
	Card *cards;                              // the array of cards
	int cards_held;                           // # cards currently in hand
	int hand_capacity;                        // # cards array can hold
};

#endif // List_dynamic_array_h
